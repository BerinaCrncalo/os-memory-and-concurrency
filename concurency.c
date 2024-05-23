#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>  // Include this for rand
#include <time.h>    // Include this for seeding the random number generator

sem_t tobacco, paper, matches;
sem_t agentSem;
sem_t tobaccoSem, paperSem, matchesSem;
sem_t mutex;

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

void* smoker_with_tobacco(void* arg) {
    while (1) {
        sem_wait(&paper);
        sem_wait(&matches);
        sem_wait(&mutex);
        // make and smoke cigarette
        printf("Smoker with tobacco smokes\n");
        sem_post(&agentSem);
        sem_post(&mutex);
    }
}

void* smoker_with_paper(void* arg) {
    while (1) {
        sem_wait(&tobacco);
        sem_wait(&matches);
        sem_wait(&mutex);
        // make and smoke cigarette
        printf("Smoker with paper smokes\n");
        sem_post(&agentSem);
        sem_post(&mutex);
    }
}

void* smoker_with_matches(void* arg) {
    while (1) {
        sem_wait(&tobacco);
        sem_wait(&paper);
        sem_wait(&mutex);
        // make and smoke cigarette
        printf("Smoker with matches smokes\n");
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

    pthread_create(&agent_thread, NULL, agent, NULL);
    pthread_create(&smoker_tobacco, NULL, smoker_with_tobacco, NULL);
    pthread_create(&smoker_paper, NULL, smoker_with_paper, NULL);
    pthread_create(&smoker_matches, NULL, smoker_with_matches, NULL);

    pthread_join(agent_thread, NULL);
    pthread_join(smoker_tobacco, NULL);
    pthread_join(smoker_paper, NULL);
    pthread_join(smoker_matches, NULL);

    return 0;
}
