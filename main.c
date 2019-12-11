
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Darwin.h"

#define BUFFER_SIZE 1024  /* Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints 
 * or comment to disable it */
#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */

struct Species *newSpecies(int sid)
{
    struct Species *temp =  (struct Species *)malloc(sizeof(struct Species));
    temp->sid = sid;
    temp->lc = temp->rc = NULL;
    return temp;
}

struct Population *newPopulation(int gid,int sid,int cid){
    struct Population *temp =  (struct Population *)malloc(sizeof(struct Population));
    temp->gid = gid;
    temp->sid = sid;
    temp->cid = cid;
    temp->lc = temp->rc = NULL;
    return temp;
}

void printPostorderSpecies(struct Species *node)
{
    if (node == NULL)
        return;

    // first recur on left subtree
    printPostorderSpecies(node->lc);

    // then recur on right subtree
    printPostorderSpecies(node->rc);

    // now deal with the node
    printf("<%d> ", node->sid);
}
void printInorderPopulation(struct Species* root,struct Population *node)
{
    if (root==NULL)
        return;
    if (node == NULL) {
        printInorderPopulation(root->lc, root->population_root);
        printInorderPopulation(root->rc,root->population_root);
    }
    printf("<%d>\n",root->sid);
    /* first recur on left child */
    printInorderPopulation(root,node->lc);

    /* then print the data of node */
    printf("<%d,%d>,", node->gid,node->cid);

    /* now recur on right child */
    printInorderPopulation(root,node->rc);
}

struct Species* search(struct Species* root, int sid)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->sid == sid)
        return root;

    // Key is greater than root's key
    if (root->sid < sid)
        return search(root->rc, sid);

    // Key is smaller than root's key
    return search(root->lc, sid);
}

struct Species *speciesInsertTree(struct Species *node, int sid){

    /* If the tree is empty, return a new node */
    if (node == NULL) return newSpecies(sid);

    /* Otherwise, recur down the tree */
    if (sid < node->sid)
        node->lc  = speciesInsertTree(node->lc, sid);
    else if (sid > node->sid)
        node->rc = speciesInsertTree(node->rc, sid);

    /* return the (unchanged) node pointer */
    return node;
}

struct Population *populationInsertTree(struct Population* node,int gid,int sid,int cid){

    /* If the tree is empty, return a new node */
    if (node == NULL) {
        return newPopulation(gid, sid, cid);
    }
    /* Otherwise, recur down the tree */
    if (gid < node->gid)
        node->lc  = populationInsertTree(node->lc, gid,sid,cid);
    else if (gid > node->gid)
        node->rc = populationInsertTree(node->rc, gid,sid,cid);

    /* return the (unchanged) node pointer */
    return node;
}
/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize (void)
{
	return 1;
}

/**
 * @brief insert new species in Species' list with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_species (int sid)
{
    if(Species_root==NULL)
        Species_root= speciesInsertTree(Species_root, sid);
    else
        speciesInsertTree(Species_root, sid);
    return 1;
}

/**
 * @brief insert new population with ID <gid> in Species' with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_population(int gid, int sid, int cid){
    struct Species* species=search(Species_root,sid);
    if(species->population_root==NULL)
        species->population_root=populationInsertTree(species->population_root,gid,sid,cid);
    else
        populationInsertTree(species->population_root,gid,sid,cid);
	return 1;
}

/**
 * @brief find the lowest (earliest) common ancestor of populations with ID <gid1> and <gid2> of species with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int lowest_common_ancestor(int sid, int gid1, int gid2){
	return 1;
}

/**
 * @brief merge species with IDs <sid1> and <sid2> into new species with ID <sid3>
 *
 * @return 1 on success
 *         0 on failure
 */
int merge_species(int sid1, int sid2, int sid3){
	return 1;
}

/**
 * @brief Distribute species' population in continents array
 *
 * @return 1 on success
 *         0 on failure
 */
int distribute(){
	return 1;
}

/**
 * @brief delete population with ID <gid> from species with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_population(int gid, int sid){
	return 1;
}

/**
 * @brief delete the species with lowest id and its populations
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_species(){
	return 1;
}

/**
 * @brief Remaining species evolve into homo sapiens.
 *
 * @return 1 on success
 *         0 on failure
 */
int evolution(){
	return 1;
}

/**
 * @brief Gather statistics on species from homo_sapiens tree
 *
 * @return 1 on success
 *         0 on failure
 */
int species_statistics(){
	return 1;
}

/**
 * @brief Gather statistics on population belonging to species with ID <sid> from homo_sapiens tree
 *
 * @return 1 on success
 *         0 on failure
 */
int population_statistics(int sid){
	return 1;
}

/**
 * @brief Print species' leaves list
 *
 * @return 1 on success
 *         0 on failure
 */
int print_species(){
    printPostorderSpecies(Species_root);
	return 1;
}

/**
 * @brief Print species' tree with population trees
 *
 * @return 1 on success
 *         0 on failure
 */
int print_populations(){
    struct Species* root=Species_root;
    printInorderPopulation(root,root->population_root);
    return 1;
}

/**
 * @brief Print continents array with each continent's population tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_continents(){
	return 1;
}

/**
 * @brief Print homo_sapiens tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_homo_sapiens(){
	return 1;
}

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */
int free_all(void)
{
	return 1;
}


/**
 * @brief The main function
 *
 * @param argc Number of arguments
 * @param argv Argument vector
 *
 * @return 0 on success
 *         1 on failure
 */
int main(int argc, char** argv)
{
	FILE *fin = NULL;
	char buff[BUFFER_SIZE], event;

	/* Check command buff arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <input_file> \n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if (( fin = fopen(argv[1], "r") ) == NULL ) {
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	/* Initializations */
	initialize();

	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin)) {

		DPRINT("\n>>> Event: %s", buff);

		switch(buff[0]) {

			/* Comment */
			case '#':
				break;

				/* Insert Species
				 * S <sid> */
			case 'S':
				{
					int sid;

					sscanf(buff, "%c %d", &event, &sid);
					DPRINT("%c %d\n", event, sid);

					if (insert_species(sid)) {
						DPRINT("%c %d succeeded\n", event, sid);
					} else {
						fprintf(stderr, "%c %d failed\n", event, sid);
					}

					break;
				}

				/* Insert population
				 * G <gid> <sid> <cid> */
			case 'G':
				{
					int gid, sid, cid;

					sscanf(buff, "%c %d %d %d", &event, &gid, &sid, &cid);
					DPRINT("%c %d %d %d\n", event, gid, sid, cid);

					if (insert_population(gid, sid, cid)) {
						DPRINT("%c %d %d %d succeeded\n", event, gid, sid, cid);
					} else {
						fprintf(stderr, "%c %d %d %d failed\n", event, gid, sid, cid);
					}

					break;
				}

				/* Lowest Common Ancestor
				 * L <sid> <gid1> <gid2> */
			 case 'L':
				{
					int sid, gid1, gid2;

					sscanf(buff, "%c %d %d %d", &event, &sid, &gid1, &gid2);
					DPRINT("%c %d %d %d\n", event, sid, gid1, gid2);

					if (lowest_common_ancestor(sid, gid1, gid2)) {
						DPRINT("%c %d %d %d succeeded\n", event, sid, gid1, gid2);
					} else {
						fprintf(stderr, "%c %d %d %d failed\n", event, sid, gid1, gid2);
					}

					break;
				}

				/* Merge species
				 * M <sid1> <sid2> <sid3> */
			case 'M':
				{
					int sid1, sid2, sid3;

					sscanf(buff, "%c %d %d %d", &event, &sid1, &sid2, &sid3);
					DPRINT("%c %d %d %d\n", event, sid1, sid2, sid3);

					if (merge_species(sid1, sid2, sid3)) {
						DPRINT("%c %d %d %d succeeded\n", event, sid1, sid2, sid3);
					} else {
						fprintf(stderr, "%c %d %d %d failed\n", event, sid1, sid2, sid3);
					}

					break;
				}

				/* Distribute species
				 * D */
			case 'D':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (distribute()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Delete population
				 * K <gid> <sid> */
			case 'K':
				{
					int gid, sid;

					sscanf(buff, "%c %d %d", &event, &gid, &sid);
					DPRINT("%c %d %d\n", event, gid, sid);

					if (delete_population(gid, sid)) {
						DPRINT("%c %d %d succeeded\n", event, gid, sid);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, gid, sid);
					}

					break;
				}

				/* Delete species
				 * F */
			case 'F':
				{
					DPRINT("%c \n", event);

					if (delete_species()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Evolution to homo sapiens
				 * E */
			case 'E':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (evolution()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Species' statistics
				 * N */
			case 'N':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (species_statistics()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Population statistics
				 * J <sid> */
			case 'J':
				{
					int sid;

					sscanf(buff, "%c %d", &event, &sid);
					DPRINT("%c %d\n", event, sid);

					if (population_statistics(sid)) {
						DPRINT("%c %d succeeded\n", event, sid);
					} else {
						fprintf(stderr, "%c %d failed\n", event, sid);
					}

					break;
				}

				/* Print species
				 * P */
			case 'P':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_species()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

			/* Print populations
				 * X */
			case 'X':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_populations()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

			/* Print continents
				 * C */
			case 'C':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_continents()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

			/* Print homo sapiens
				 * W */
			case 'W':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_homo_sapiens()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Empty line */
			case '\n':
				break;

				/* Ignore everything else */
			default:
				DPRINT("Ignoring buff: %s \n", buff);

				break;
		}
	}

	free_all();
	return (EXIT_SUCCESS);
}
