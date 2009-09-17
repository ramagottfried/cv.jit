/*
max.cv.jit.blobs.recon
	

Copyright 2008, Jean-Marc Pelletier
jmp@iamas.ac.jp

This file is part of cv.jit.

cv.jit is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published 
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

cv.jit is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with cv.jit.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifdef __cplusplus
extern "C" {
#endif
#include "jit.common.h"
#include "max.jit.mop.h"
#ifdef __cplusplus 
} //extern "C"
#endif

typedef struct _max_cv_jit_blobs_recon 
{
	t_object		ob;
	void			*obex;
} t_max_cv_jit_blobs_recon;

t_jit_err cv_jit_blobs_recon_init(void); 

void *max_cv_jit_blobs_recon_new(t_symbol *s, long argc, t_atom *argv);
void max_cv_jit_blobs_recon_free(t_max_cv_jit_blobs_recon *x);

void *max_cv_jit_blobs_recon_class;
	
#ifdef __cplusplus
extern "C"
#endif
int main(void)
{	
	void *p,*q;
	
	cv_jit_blobs_recon_init();
	setup(
			(t_messlist **)&max_cv_jit_blobs_recon_class,	//A pointer to the Max class pointer
			(method)max_cv_jit_blobs_recon_new,			//The constructor function
			(method)max_cv_jit_blobs_recon_free,			//The destructor function
			(short)sizeof(t_max_cv_jit_blobs_recon),		//The size of the Max class
			0L,											//Use only for GUI objects, null for standard Jitter objects
			A_GIMME,									//Pass arguments as a list of t_atoms
			0);											//End of type list

	p = max_jit_classex_setup(calcoffset(t_max_cv_jit_blobs_recon,obex));	//Setup Max class
	q = jit_class_findbyname(gensym("cv_jit_blobs_recon"));				//Get a pointer to the Jitter object class
    max_jit_classex_mop_wrap(p,q,0); 		
    max_jit_classex_standard_wrap(p,q,0); 	

    addmess((method)max_jit_mop_assist, "assist", A_CANT,0);	//Add outlet assistance to object
	
	return 0;
}

void max_cv_jit_blobs_recon_free(t_max_cv_jit_blobs_recon *x)
{
	max_jit_mop_free(x);		//Free the matrix operator
	jit_object_free(max_jit_obex_jitob_get(x));	//Free the Jitter object
	max_jit_obex_free(x);		//Free the Max wrapper object
}

void *max_cv_jit_blobs_recon_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_cv_jit_blobs_recon *x;
	void *o;

	if (x=(t_max_cv_jit_blobs_recon *)max_jit_obex_new(max_cv_jit_blobs_recon_class,gensym("cv_jit_blobs_recon"))) {
		if (o=jit_object_new(gensym("cv_jit_blobs_recon"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);			
			max_jit_attr_args(x,argc,argv);
		} else {
			error("cv.jit.blobs.recon: could not allocate object");
			freeobject((t_object *)x);
		}
	}
	return (x);
}
