#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __tree
{
    int val;
    struct __tree* right;
    struct __tree* left;
    int height;
}TREE;

/** \brief
 *  insert node in tree
 *
 * \param TREE** root of tree
 * \param int inserts nodes val
 * \return void
 *
 */
void insertToTree(TREE**, int);

/** \brief
 *  count balance factor of node
 *
 * \param TREE* node
 * \return int
 *
 */
int balanceFactor(TREE*);

/** \brief
 *  corrects nodes height
 *
 * \param TREE* node
 * \return void
 *
 */
void restoreHeight(TREE*);

/** \brief
 *  left rotate
 *
 * \param TREE* node
 * \return TREE*
 *
 */
TREE* turnLeft(TREE*);

/** \brief
 *   right rotate
 *
 * \param TREE* node
 * \return TREE*
 *
 */
TREE* turnRight(TREE*);

/** \brief
 *  balancing node
 *
 * \param TREE* node
 * \return TREE*
 *
 */
TREE* balance(TREE*);

/** \brief
 *  destroy tree
 *
 * \param TREE** root
 * \return void
 *
 */
void deleteTree(TREE**);

/** \brief
 *  print tree height
 *
 * \param root TREE* root
 * \return void
 *
 */
void printHeight(TREE* root);

#endif /* HEAD_H_INCLUDED*/
