
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
struct ContinentPopulation* newContinentPopulation(int gid){
    struct ContinentPopulation *temp =  (struct ContinentPopulation *)malloc(sizeof(struct ContinentPopulation));
    temp->gid = gid;
    temp->lc = temp->rc = NULL;
    return temp;
}

struct HomoSapiens* newHomo(int sid){
    struct HomoSapiens *temp =  (struct HomoSapiens *)malloc(sizeof(struct HomoSapiens));
    temp->sid = sid;
    temp->lc = temp->rc = NULL;
    return temp;
}
struct Population* lca(struct Population* root,int gid1,int gid2){
    if(root==NULL)
        return NULL;
    if(root->gid >  gid1 && root->gid > gid2){
        return lca(root->lc,gid1,gid2);
    }
    if(root->gid <  gid1 && root->gid < gid2) {
        return lca(root->rc,gid1,gid2);
    }
    return root;
}

void printPostorderSpecies(struct Species *node)
{
    if (node == NULL)
        return;

    // first recur on left subtree
    printPostorderSpecies(node->lc);
    printf("<%d> ", node->sid);
    // then recur on right subtree
    printPostorderSpecies(node->rc);

    // now deal with the node

}
void printInorderPopulation(struct Population *node) {
    if (node == NULL)
        return;
    /* first recur on left child */
    printInorderPopulation(node->lc);
    /* then print the data of node */
    printf("<%d,%d> ", node->gid, node->cid);
    printInorderPopulation(node->rc);
    /* now recur on right child */
}
void printHomoPopulation(struct Population *node) {
    if (node == NULL)
        return;
    /* first recur on left child */
    printInorderPopulation(node->lc);
    /* then print the data of node */
    printf("<%d,%d> ", node->gid, node->sid);
    printInorderPopulation(node->rc);
    /* now recur on right child */
}
void printSpeciesPopulation(struct Species* node){
    {
        if (node == NULL)
            return;
        // first recur on left subtree
        printSpeciesPopulation(node->lc);
        printf("\n<%d>\n ", node->sid);
        printInorderPopulation(node->population_root);
        printSpeciesPopulation(node->rc);

        // now deal with the node


    }
}
struct Species* searchSpecies(struct Species* root, int sid)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->sid == sid)
        return root;

    // Key is greater than root's key
    if (root->sid < sid)
        return searchSpecies(root->rc, sid);

    // Key is smaller than root's key
    return searchSpecies(root->lc, sid);
}
struct Population* searchPopulation(struct Population* root, int gid){
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->gid == gid)
        return root;

    // Key is greater than root's key
    if (root->gid < gid)
        return searchPopulation(root->rc, gid);

    // Key is smaller than root's key
    return searchPopulation(root->lc, gid);
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
struct Species * minValueNodeSpecies(struct Species* node)
{
    struct Species* current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->lc != NULL)
        current = current->lc;
    return current;
}
struct Population * minValueNodePopulation(struct Population* node)
{
    struct Population* current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->lc != NULL)
        current = current->lc;
    return current;
}
struct ContinentPopulation * minValueNodeContinentPopulation(struct ContinentPopulation* node)
{
    struct ContinentPopulation* current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->lc != NULL)
        current = current->lc;
    return current;
}

struct HomoSapiens * minValueNodeHomo(struct HomoSapiens* node)
{
    struct HomoSapiens* current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->lc != NULL)
        current = current->lc;
    return current;
}
struct Species* deleteSpecie(struct Species* root,int sid){
    struct Species *check=Species_root;
    if(root==NULL)
        return root;
    if(sid<root->sid)
        root->lc=deleteSpecie(root->lc,sid);
    else if(sid>root->sid)
        root->rc=deleteSpecie(root->rc,sid);
    else{
        if(root->lc == NULL && root->rc == NULL)
        {
            root= NULL;
        }
        else if (root->lc == NULL)
        {
            root=root->rc;
        }
        else if (root->rc == NULL)
        {
            root=root->lc;
        }
        else {
            struct Species *temp = minValueNodeSpecies(root->rc);
            root->sid = temp->sid;
            root->population_root = temp->population_root;
            root->rc = deleteSpecie(root->rc, temp->sid);
        }
    }
    return root;
}

void  copySpecies(struct Population* population, int sid){
    if (population == NULL)
        return;
    // first recur on left subtree
    copySpecies(population->lc, sid);
    insert_population(population->gid,sid,population->cid);
    // then recur on right subtree
    copySpecies(population->rc, sid);
}

struct  ContinentPopulation* insertContinent(struct ContinentPopulation* node,int gid){
    if(node==NULL)
        return newContinentPopulation(gid);
    if (gid < node->gid)
        node->lc  = insertContinent(node->lc, gid);
    else if (gid > node->gid)
        node->rc = insertContinent(node->rc, gid);
}
void distributeRec(struct Population* population){
    if(population==NULL)
        return;
    if(continents[population->cid]->population_root==NULL)
        continents[population->cid]->population_root=insertContinent(continents[population->cid]->population_root,population->gid);
    else
        insertContinent(continents[population->cid]->population_root,population->gid);
    distributeRec(population->lc);
    distributeRec(population->rc);
}
void distributeSpecies(struct Species* species){
    if(species==NULL)
        return;
    distributeRec(species->population_root);
    distributeSpecies(species->lc);
    distributeSpecies(species->rc);
}
void printContinent(struct ContinentPopulation* node){
    if (node == NULL)
        return;
    /* first recur on left child */
    printContinent(node->lc);
    /* then print the data of node */
    printf("<%d>  ", node->gid);
    printContinent(node->rc);
}

struct ContinentPopulation* searchContinent(struct ContinentPopulation* root,int gid){
    if (root == NULL || root->gid == gid)
        return root;

    // Key is greater than root's key
    if (root->gid < gid)
        return searchContinent(root->rc, gid);

    // Key is smaller than root's key
    return searchContinent(root->lc, gid);
}

struct Population* deletePopulation(struct Population* root,int gid,struct Species* species)
    {
        // base case
        if (root == NULL) return root;

        // If the key to be deleted is smaller than the root's key,
        // then it lies in left subtree
        if (gid < root->gid)
            root->lc = deletePopulation(root->lc, gid,species);

            // If the key to be deleted is greater than the root's key,
            // then it lies in right subtree
        else if (gid > root->gid)
            root->rc = deletePopulation(root->rc, gid,species);

            // if key is same as root's key, then This is the node
            // to be deleted
        else
        {
            // node with only one child or no child
            if (root->lc == NULL)
            {
                struct Population *temp = root->rc;
                free(root);
                return temp;
            }
            else if (root->rc == NULL)
            {
                struct Population *temp = root->lc;
                free(root);
                return temp;
            }
            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            struct Population* temp = minValueNodePopulation(root->rc);

            // Copy the inorder successor's content to this node
            root->gid = temp->gid;
            // Delete the inorder successor
            root->rc = deletePopulation(root->rc, temp->gid,species);
        }
        return root;
    }

    struct ContinentPopulation* deleteContinentPopulation(struct ContinentPopulation* root,int gid)
        {
            // base case
            if (root == NULL) return root;

            // If the key to be deleted is smaller than the root's key,
            // then it lies in left subtree
            if (gid < root->gid)
                root->lc = deleteContinentPopulation(root->lc, gid);

                // If the key to be deleted is greater than the root's key,
                // then it lies in right subtree
            else if (gid > root->gid)
                root->rc = deleteContinentPopulation(root->rc, gid);

                // if key is same as root's key, then This is the node
                // to be deleted
            else
            {
                // node with only one child or no child
                if (root->lc == NULL)
                {
                    struct ContinentPopulation *temp = root->rc;
                    free(root);
                    return temp;
                }
                else if (root->rc == NULL)
                {
                    struct ContinentPopulation *temp = root->lc;
                    free(root);
                    return temp;
                }

                // node with two children: Get the inorder successor (smallest
                // in the right subtree)
                struct ContinentPopulation* temp = minValueNodeContinentPopulation(root->rc);

                // Copy the inorder successor's content to this node
                root->gid = temp->gid;


                // Delete the inorder successor
                root->rc = deleteContinentPopulation(root->rc, temp->gid);
            }
            return root;
        }

void deletePopulationTree(struct Population* node)
{
    if (node == NULL)
        return;
    /* first delete both subtrees */
    deletePopulationTree(node->lc);
    deletePopulationTree(node->rc);
    /* then delete the node */
    free(node);
}
void deleteSpeciesTree(struct Population* node)
{
    if (node == NULL)
        return;
    /* first delete both subtrees */
    deleteSpeciesTree(node->lc);
    deleteSpeciesTree(node->rc);
    /* then delete the node */
    free(node);
}

struct HomoSapiens* moveSpecies(struct Species* species, struct HomoSapiens* homoSapiens){
    if(species==NULL)
        return NULL;
    homoSapiens=newHomo(species->sid);
    homoSapiens->population_root=species->population_root;
    struct HomoSapiens* lchild=moveSpecies(species->lc,homoSapiens->lc);
    homoSapiens->lc=lchild;
    if(lchild!=NULL)
        lchild->parent=homoSapiens;
    struct HomoSapiens* rchild=moveSpecies(species->rc,homoSapiens->rc);
    homoSapiens->rc=rchild;
    if(rchild!=NULL)
        rchild->parent=homoSapiens;
    return homoSapiens;
}
struct HomoSapiens * inOrderSuccessor(struct HomoSapiens *n)
{
    // step 1 of the above algorithm
    if( n->rc != NULL )
        return minValueNodeHomo(n->rc);

    // step 2 of the above algorithm
    struct HomoSapiens *p = n->parent;
    while(p != NULL && n == p->rc)
    {
        n = p;
        p = p->parent;
    }
    return p;
}
void fixnext(struct HomoSapiens* root){
    if(root==NULL)
        return;
    root->next=inOrderSuccessor(root);
    fixnext(root->lc);
    fixnext(root->rc);
}

void printHomoSapiens(struct HomoSapiens* root){
    if(root==NULL)
        return;
    printf("|");
    printHomoPopulation(root->population_root);
    printf("| ");
    printHomoSapiens(root->lc);
    printHomoSapiens(root->rc);
}

int countSid(struct HomoSapiens* node){
    struct HomoSapiens *root=minValueNodeHomo(node);
    int count=0;
    while (root!=NULL){
        count++;
        root=root->next;
    }
    return count;
}

int countPopulation(struct Population *tree)
{
    int c =  1;             //Node itself should be counted
    if (tree ==NULL)
        return 0;
    else
    {
        c += countPopulation(tree->lc);
        c += countPopulation(tree->rc);
        return c;
    }
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
    print_species();
    return 1;
}

/**
 * @brief insert new population with ID <gid> in Species' with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_population(int gid, int sid, int cid){
    struct Species* species= searchSpecies(Species_root, sid);
    if(species->population_root==NULL)
        species->population_root=populationInsertTree(species->population_root,gid,sid,cid);
    else
        populationInsertTree(species->population_root,gid,sid,cid);
    print_populations();
	return 1;
}

/**
 * @brief find the lowest (earliest) common ancestor of populations with ID <gid1> and <gid2> of species with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int lowest_common_ancestor(int sid, int gid1, int gid2) {
    struct Species* species=searchSpecies(Species_root,sid);
    struct Population* population=species->population_root;
    struct Population* ancestor=lca(population,gid1,gid2);
    printf("\nL <%d> <%d> <%d>\n",sid,gid1,gid2);
    printf("Lowest Common Ancestor: <%d>\n",ancestor->gid);
    return 1;
}

/**
 * @brief merge species with IDs <sid1> and <sid2> into new species with ID <sid3>
 *
 * @return 1 on success
 *         0 on failure
 */
int merge_species(int sid1, int sid2, int sid3){
    struct Species* species1=searchSpecies(Species_root,sid1);
    struct Species* species2=searchSpecies(Species_root,sid2);
    struct Species* node=Species_root;
    if(species1==NULL || species2==NULL)
        return 0;
    insert_species(sid3);
    copySpecies(species1->population_root, sid3);
    copySpecies(species2->population_root, sid3);
    deleteSpecie(Species_root,sid1);
    deleteSpecie(Species_root,sid2);
    print_populations();
    return 1;
}

/**
 * @brief Distribute species' population in continents array
 *
 * @return 1 on success
 *         0 on failure
 */
int distribute(){
    for (int i = 0; i <5 ; ++i) {
        continents[i]=(struct ContinentTree *)malloc(sizeof(struct ContinentTree));
        continents[i]->sentinel=(struct ContinentPopulation *)malloc(sizeof(struct ContinentPopulation));
        continents[i]->sentinel->gid=-1;
    }
    distributeSpecies(Species_root);
    print_continents();
	return 1;
}

/**
 * @brief delete population with ID <gid> from species with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_population(int gid, int sid){
    struct Species* species=searchSpecies(Species_root,sid);
    struct Population* population=searchPopulation(species->population_root,gid);
    struct ContinentPopulation* continentPopulation=continents[population->cid]->population_root;
    deleteContinentPopulation(continentPopulation,gid);
   species->population_root=deletePopulation(species->population_root,gid,species);
   printf("SPECIES\n");
   print_populations();
   printf("\nCONTINENTS\n");
   print_continents();
	return 1;
}

/**
 * @brief delete the species with lowest id and its populations
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_species(){
    struct Species* node=Species_root;
    struct Species* minSpecie= minValueNodeSpecies(Species_root);
    deletePopulationTree(minSpecie->population_root);
   deleteSpecie(Species_root,minSpecie->sid);
    printf("SPECIES\n");
    print_populations();
    printf("\nCONTINENTS\n");
    print_continents();
	return 1;
}

/**
 * @brief Remaining species evolve into homo sapiens.
 *
 * @return 1 on success
 *         0 on failure
 */
int evolution(){
    struct Species* checkS=Species_root;
    Homo_Sapiens_root=moveSpecies(Species_root,Homo_Sapiens_root);
    struct HomoSapiens* check=Homo_Sapiens_root;
    struct HomoSapiens* node=minValueNodeHomo(Homo_Sapiens_root);
    fixnext(Homo_Sapiens_root);
    printHomoSapiens(Homo_Sapiens_root);
    printf("\n");

	return 1;
}

/**
 * @brief Gather statistics on species from homo_sapiens tree
 *
 * @return 1 on success
 *         0 on failure
 */
int species_statistics(){
    struct HomoSapiens *check=Homo_Sapiens_root;
    int count=countSid(Homo_Sapiens_root);
    struct HomoSapiens* node=minValueNodeHomo(Homo_Sapiens_root);
    printf("Homo Sapiens: ");
    while (node!=NULL){
        printf("<%d>,",node->sid);
        node=node->next;
    }
    printf("\nHomo Sapiens species: %d\n",count);
	return 1;
}

/**
 * @brief Gather statistics on population belonging to species with ID <sid> from homo_sapiens tree
 *
 * @return 1 on success
 *         0 on failure
 */
int population_statistics(int sid){
    struct HomoSapiens* node=minValueNodeHomo(Homo_Sapiens_root);
    while (node->sid!=sid && node->next!=NULL){
        node=node->next;
    }
    int count=countPopulation(node->population_root);
    printf("Homo Sapiens populations: %d\n",count);
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
    printSpeciesPopulation(root);
    return 1;
}

/**
 * @brief Print continents array with each continent's population tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_continents(){
    for (int i = 0; i <5 ; ++i) {
        printf("\nContinent %d: ",i);
        printContinent(continents[i]->population_root);
        printf("\n");
    }
	return 1;
}

/**
 * @brief Print homo_sapiens tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_homo_sapiens(){
    printHomoSapiens(Homo_Sapiens_root);
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
