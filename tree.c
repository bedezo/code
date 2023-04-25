#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
	int value;
	struct tree *tleft;
	struct tree *tright;
	struct tree *parent; // cette variable n'est pas obligatoire, c'est juste pour une bonne affichage, vous pouvez ne pas le mettre
}tree;

tree *new_tree(int x) // creation d'une nouvelle arbre
{
	tree *tr = malloc(sizeof(*tr));
	if(tr == NULL)
	{
		printf("Erreur d'allocation dynamique\n");
		exit(1);
	}
	tr->value = x;
	tr->tleft = NULL;
	tr->tright = NULL;
	tr->parent = NULL;
	//printf("Creation de %d\n",tr->value);
	return tr;
}

tree *join_tree(tree *left, tree *right,int node) // joindre plusieurs arbres
{
	tree *tr = new_tree(node);

	tr->tleft = left;
	tr->tright = right;

	if(left != NULL)
		left->parent = tr;
	if(right != NULL)
		right->parent = tr;
	return tr;
}

void clear_tree(tree *tr) // libere les espaces memoires allouer pour chaque element de l'arbre
{
	if(tr == NULL)
		return;

	//printf("Suppression de %d\n",tr->value);

	clear_tree(tr->tleft);
	clear_tree(tr->tright);
	free(tr);
}

void print_tree_prefixe(tree *tr) // Affichage prefixe (R G D)
{
	if(tr == NULL)
		return;
	if(tr->parent != NULL)
		printf("(%d) -> %d\n",tr->parent->value,tr->value);
	else
		printf("(%d)\n",tr->value);

	if(tr->tleft != NULL)
		print_tree_prefixe(tr->tleft);
	if(tr->tright != NULL)
		print_tree_prefixe(tr->tright);
}

void print_tree_infixe(tree *tr) // Affichage infixe (G R D)
{
	//tree *t = tr->tleft;
	if(tr == NULL)
		return;
	if(tr->tleft != NULL)
		print_tree_infixe(tr->tleft);
	if(tr->parent != NULL)
		printf("(%d) -> %d\n",tr->parent->value,tr->value);
	else
		printf("(%d)\n",tr->value);
	if(tr->tright != NULL)
		print_tree_infixe(tr->tright);

}

void print_tree_postfixe(tree *tr) // Affichage postfixe (G D R)
{
	if(tr == NULL)
		return;

	if(tr->tleft != NULL)
		print_tree_infixe(tr->tleft);
	
	if(tr->tright != NULL)
		print_tree_infixe(tr->tright);

	if(tr->parent != NULL)
		printf("(%d) -> %d\n",tr->parent->value,tr->value);
	else
		printf("(%d)\n",tr->value);
}

tree *insertNode(tree *tr, int x) {
    if(tr == NULL) {
    tree *t = new_tree(x);
    return t;
    }
    else {
        if(x <= tr->value) {
            tr->tleft = insertNode(tr->tleft,x);
        }
        else {
            tr->tright = insertNode(tr->tright,x);
        }
        return tr;
    }
}

int count_tree_nodes(tree *tr) // compte le nombre de noeuds
{
	if(tr == NULL)
		return 0;
	else
		return 1 + count_tree_nodes(tr->tleft) + count_tree_nodes(tr->tright);
}

int main(int argc, char const *argv[])
{
	tree *arbre = NULL;
	int i;
  
	arbre = join_tree(join_tree(join_tree(join_tree(NULL,NULL,3),NULL,2), // definition de l'arbre c'est la mm chose que celle de dessous
		join_tree(join_tree(NULL,NULL,5),join_tree(NULL,NULL,6),4),1),
		join_tree(join_tree(NULL,join_tree(join_tree(NULL,NULL,11),
		join_tree(NULL,NULL,12),10),9),join_tree(join_tree(NULL,NULL,14),
		join_tree(NULL,NULL,15),13),8),0);
    
	/*for(i = 0;i <= 15;i++) // la methode que le prof a utiliser pour la definition de l'arbre
		arbre = insertNode(arbre,i);*/
    
	print_tree_prefixe(arbre);
	printf("\n");
	print_tree_infixe(arbre);
	printf("l'arbre contient %d noeud(s)\n",count_tree_nodes(arbre));
	clear_tree(arbre);
	return 0;
}
