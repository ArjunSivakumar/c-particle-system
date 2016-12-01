/*
 * particle.c
 *
 *  Created on: Nov 14, 2016
 *      Author: siva0044
 */

/* Name: Arjun Sivakumar
 Course: CST8234 - C Programming
 Notes: Assignment 2 - Particle System
 Date: November 7, 2016
 */
#include "Sivakumar_particle.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/*********************************************************************
* FUNCTION : particle_init
* PURPOSE : initialize the properties of a single particle
* INPUT : pointer to the particle structure to be initialized
* OUTPUT : returns 1
on error, 0 on success
* NOTES :
*********************************************************************/
int particle_init(struct particle* p) {

	/*Using method to generate random colours */
	p->col.r = generate_float(0, 1);
	p->col.g = generate_float(0, 1);
	p->col.b = generate_float(0, 1);
	p->col.a = generate_float(0, 1);

	/* Centering position of each particle */
	p->pos.x = 0.0;
	p->pos.y = 0.0;
	p->pos.z = 0.0;

	/* Initial direction of each particle is 0 */
	p->dir.x = generate_float(0, 1);
	p->dir.y = generate_float(0, 1);
	p->dir.z = generate_float(0, 1);

	/* Initial speed of each particle is 0 */
	p->spd.x = generate_float(0, 1);
	p->spd.y = generate_float(0, 1);
	p->spd.z = generate_float(0, 1);

	/* Lifespan of each particle is 100 */
	p->lifespan = 100;

	/* Using method to generate random sizes for each particle */
	p->size = generate_float(0, 5);

	return 0;

}

/*********************************************************************
* FUNCTION : particle_add
* PURPOSE : add a particle to the dynamic particle linked list
* INPUT : struct particle *head. Head of the particle list
* OUTPUT : returns 1
on error, 0 on success
* NOTES : Calls particle_init()
********************************************************************/
int particle_add(struct particle **head) {

	struct particle* newParticle;
	newParticle = (struct particle*) malloc(sizeof(struct particle));
	newParticle->next = *head;
	*head = newParticle;
	particle_init(newParticle);
	return 0;

}
/*********************************************************************
* FUNCTION : particle_remove
* PURPOSE : remove a specific particle from the dynamic
*	    particle linked list
* INPUT : pointer to the particle to remove
* OUTPUT : returns 1
* on error, 0 on success
* NOTES : Particle can be situated in any place in the list.
* Usually deleted because the lifespan ran out
********************************************************************/
int particle_remove(struct particle* p) {

	struct particle* temp = p->next;

	if (temp == NULL) {

		return -1;

	}

	else {

		p = temp;
		temp = NULL;

	}

	return 0;

}
/*********************************************************************
* FUNCTION : particle_destroy
* PURPOSE : free memory used by the dynamic particle linked list
* INPUT : struct particle **head. Head of the particle list
* OUTPUT : returns 1 on error, the number of particles destroyed on success
* NOTES : removes all particles from the list
*	  Calls particle_remove()
********************************************************************/
int particle_destroy(struct particle **head) {

	int count;
	struct particle *temp = *head;

	if (temp == NULL) {
		return -1;
	}

	else {

		while (temp != NULL) {
			particle_remove(temp);
			temp = temp->next;
			count++;
		}

	}

	return count;

}
/********************************************************************
* FUNCTION : particle_update
* PURPOSE : update the particles properties to be rendered
*           in the next frame
* INPUT : struct particle **head. Head of the particle list
* OUTPUT : returns 1 on error, 0 on success
* NOTES : Creativity and more creativity here for you !!!
********************************************************************/
int particle_update(struct particle **head) {
	
	struct particle* p = *head;

	srand(time(0));

	/* While the particle pointer does not point to null*/
	while (p != NULL) {

		p->lifespan -= DELTA_LIFE_SPAN;

		/* As time progresses through the simulation the position of each particle is changed */
		p->pos.x = (p->pos.x + ( (p->spd.x * generate_float(0,1) ) * p->dir.x * 0.00000001) * generate_float(-1, 1))
				- generate_float(-1, 1);

		p->pos.y = (p->pos.y + ((p->spd.y * generate_float(0,1) )* p->dir.y * 0.00000001) * generate_float(-1, 1))
				- generate_float(-1, 1);

		/* Remove the particle from the list after the life-span reaches 0*/
		if (p->lifespan > 0) {

			particle_remove(p);

		}

		/* Points to next item in linked list */
		p = p->next;
	}

	return 0;

}

float generate_float(int min, int max) {

	float randFloat;

	randFloat = rand() % (max - min + 1) + min;

	return randFloat;

}


