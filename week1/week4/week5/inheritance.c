#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
#define GENERATIONS 3
#define INDENT_LENGTH 4

typedef struct person
{
    struct person *parents[2];   // NULL if no parents
    char alleles[2];             // 'A', 'B', or 'O'
} person;

// Function prototypes
person *create_family(int generations);
void free_family(person *p);
void print_family(person *p, int generation);
char random_allele(void);

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);

    return 0;
}

// ---------------------------------------------------------------------------
// TODO 1: create_family
// ---------------------------------------------------------------------------
person *create_family(int generations)
{
    // Allocate memory for a new person
    person *p = malloc(sizeof(person));
    if (p == NULL)
    {
        return NULL;
    }

    // If there are still generations left to create
    if (generations > 1)
    {
        // Recursively create two parents for the current person
        p->parents[0] = create_family(generations - 1);
        p->parents[1] = create_family(generations - 1);

        // Randomly inherit one allele from each parent
        // rand() % 2 picks index 0 or 1 from the parent's alleles array
        p->alleles[0] = p->parents[0]->alleles[rand() % 2];
        p->alleles[1] = p->parents[1]->alleles[rand() % 2];
    }
    // Oldest generation (Grandparents)
    else
    {
        // No parents to point to
        p->parents[0] = NULL;
        p->parents[1] = NULL;

        // Assign random alleles since they have no parents in the simulation
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }

    // Return the newly created person
    return p;
}

// ---------------------------------------------------------------------------
// TODO 2: free_family
// ---------------------------------------------------------------------------
void free_family(person *p)
{
    // Base case: if pointer is NULL, there is nothing to free
    if (p == NULL)
    {
        return;
    }

    // Recursively free both parents first
    // This ensures we don't lose the pointers to the parents before freeing them
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Finally, free the current person
    free(p);
}

// ---------------------------------------------------------------------------
// Distribution code below — do not modify
// ---------------------------------------------------------------------------

void print_family(person *p, int generation)
{
    if (p == NULL)
    {
        return;
    }

    // Print parents before child
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);

    // Indent based on generation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print label and blood type
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
}

char random_allele(void)
{
    int r = rand() % 3;
    if (r == 0) return 'A';
    if (r == 1) return 'B';
    return 'O';
}
