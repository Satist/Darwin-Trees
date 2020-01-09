#ifndef __DARWIN_H__
#define __DARWIN_H__

struct Species{
	int					sid;
	struct Species		*next;	
	struct Population	*population_root;
	struct Species		*lc;
	struct Species		*rc;
};

struct Population{
	int					gid;
	int					sid;
	int					cid;
	struct Population	*parent;
	struct Population	*lc;
	struct Population	*rc;
};

struct ContinentPopulation{
	int 						gid;
	struct ContinentPopulation	*lc;
	struct ContinentPopulation	*rc;
};

struct ContinentTree{
	struct ContinentPopulation *population_root;
	struct ContinentPopulation *sentinel;
};

struct HomoSapiens{
	int					sid;
	struct Population	*population_root;
	struct HomoSapiens   *parent;
	struct HomoSapiens	*next;
	struct HomoSapiens	*lc;
	struct HomoSapiens	*rc;
};

/*
 * Global variables
 *
 */

struct ContinentTree *continents[5]; // Continents' array. Each element is two pointers. 
									 // One to the continent's population tree root
									 // and one to the tree's sentinel node

struct Species *Species_root; // Pointer to the root of Species' tree


struct HomoSapiens *Homo_Sapiens_root; // Pointer to the root of Homo Sapiens tree

int insert_population(int gid, int sid, int cid);
int insert_species (int sid);
int lowest_common_ancestor(int sid, int gid1, int gid2) ;
int merge_species(int sid1, int sid2, int sid3);
int distribute();
int delete_population(int gid, int sid);
int delete_species();
int evolution();
int species_statistics();
int population_statistics(int sid);
int print_species();
int print_populations();
int print_continents();
int print_homo_sapiens();

#endif /* __DARWIN_H__ */
