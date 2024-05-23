#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

sem_t tobacco, paper, matches, agentSem, mutex;

void* agent(void* arg) {
    while (1) {
        sem_wait(&agentSem);
        int r = rand() % 3;
        if (r == 0) {
            sem_post(&tobacco);
            sem_post(&paper);
        } else if (r == 1) {
            sem_post(&tobacco);
            sem_post(&matches);
        } else {
            sem_post(&paper);
            sem_post(&matches);
        }
    }
}

void* smoker(void* arg) {
    sem_t *first = ((sem_t**)arg)[0];
    sem_t *second = ((sem_t**)arg)[1];
    while (1) {
        sem_wait(first);
        sem_wait(second);
        sem_wait(&mutex);
        printf("Smoker smokes\n");
        sem_post(&agentSem);
        sem_post(&mutex);
    }
}

int main() {
    pthread_t agent_thread, smoker_tobacco, smoker_paper, smoker_matches;

    sem_init(&tobacco, 0, 0);
    sem_init(&paper, 0, 0);
    sem_init(&matches, 0, 0);
    sem_init(&agentSem, 0, 1);
    sem_init(&mutex, 0, 1);

    sem_t *args_tobacco[] = {&paper, &matches};
    sem_t *args_paper[] = {&tobacco, &matches};
    sem_t *args_matches[] = {&tobacco, &paper};

    pthread_create(&agent_thread, NULL, agent, NULL);
    pthread_create(&smoker_tobacco, NULL, smoker, args_tobacco);
    pthread_create(&smoker_paper, NULL, smoker, args_paper);
    pthread_create(&smoker_matches, NULL, smoker, args_matches);

    pthread_join(agent_thread, NULL);
    pthread_join(smoker_tobacco, NULL);
    pthread_join(smoker_paper, NULL);
    pthread_join(smoker_matches, NULL);

    return 0;
}
