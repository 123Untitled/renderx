/*****************************************************************************/
/*                                                                           */
/*      dMP dMP .aMMMb  dMP dMMMMb                                           */
/*     dMP dMP dMP"dMP amr dMP VMP                                           */
/*    dMP dMP dMP dMP dMP dMP dMP                                            */
/*    YMvAP  dMP aMP dMP dMP.aMP                                             */
/*     VP    VMMMP  dMP dMMMMP                                               */
/*                                                                           */
/*       dMMMMMP dMMMMb   aMMMMP dMP dMMMMb  dMMMMMP                         */
/*      dMP     dMP dMP dMP     amr dMP dMP dMP                              */
/*     dMMMP   dMP dMP dMP MMP dMP dMP dMP dMMMP                             */
/*    dMP     dMP dMP dMP.dMP dMP dMP dMP dMP                                */
/*   dMMMMMP dMP dMP  VMMMP" dMP dMP dMP dMMMMMP                             */
/*                                                                           */
/*****************************************************************************/

#ifndef ___void_engine_octree___
#define ___void_engine_octree___


#include <simd/simd.h>

namespace ve {
	using vec3f = simd::float3;
}


#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a>b)?b:a)



// -- V E  N A M E S P A C E --------------------------------------------------

namespace ve {


	// -- O C T R E E ---------------------------------------------------------

	template <typename ___type>
	class octree final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = ve::octree<___type>;


			// -- private members ---------------------------------------------

			// les coordonnées cartésiennes (avant passage à l'echelle)
			unsigned int posxyz[3];

			// l'exposant courant
			unsigned int e;

			// un pointeur sur la racine, un pointeur de pointeur sur la racine et les autres niveau
			//Octree<T>* tab[EMAX+1];

			// coordonnées d'offset (translation=(0,0,0) correspond à une origine au coin du cube racine)
			//Vect3f translation;

			// facteur d'échelle (la taille du cube racine est égale à scale*2^EMAX)
			float scale,_scale;


			enum a: unsigned {
				// 32 bits max exponent (31 is the sign bit, 32 is out of range)
				EMAX = 31U,
				OCT_MASQ = ((1U << EMAX) - 1U)
			};

			//#define EMAX     ((unsigned int)31)  //EXPOSANT maximal en 32 bit (à 31 on touche le bit de signe, à 32 on sort)
			//#define OCT_MASQ  ((1<<EMAX)-1)


			union uint_float {
				unsigned int i;
				float        f;
			};


			// -- private classes ---------------------------------------------

			/* octree node */
			class node final {


				private:

					// -- private members -------------------------------------

					/* data */
					___type _data; // called "node" in the original code

					/* childs */
					node* _childs[8U]; // called "ptr" in the original code (was a raw pointer)
					// node* childs;


				public:

					// -- public lifecycle ------------------------------------

					/* default constructor */
					node(void) noexcept
					: _data{}, _childs{} {
					}

					// constructeur copie
					node(const node& oct2) {

						// old code
					//:node() {
					//	ptr=NULL;
					//	*this=oct2;
					}

					// constructeur copie
					void link(const node& oct2) {
						// old code
						//ptr=oct2.ptr;
						//node=oct2.node;
					}

					// constructeur allocation récursive
					node(int n) {
					// old code
					//: node(){
					//	splitrec(n);
					}


					~node(void) noexcept {
						// old code
						// delete[] ptr;ptr=NULL;
					}


					void operator=(const node& oct2) {
						// copie récursive
						//if(ptr!=NULL)delete[] ptr;
						//ptr=NULL;
						//node=oct2.node;
						//if(oct2.ptr!=NULL){
						//	split();
						//	ptr[0]=oct2.ptr[0];
						//	ptr[1]=oct2.ptr[1];
						//	ptr[2]=oct2.ptr[2];
						//	ptr[3]=oct2.ptr[3];
						//	ptr[4]=oct2.ptr[4];
						//	ptr[5]=oct2.ptr[5];
						//	ptr[6]=oct2.ptr[6];
						//	ptr[7]=oct2.ptr[7];
						//}
					}

					void splitrec(int n) {//division récursive de l'Octree
						//if(n>0){
						//	split();
						//	ptr[0].splitrec(n-1);
						//	ptr[1].splitrec(n-1);
						//	ptr[2].splitrec(n-1);
						//	ptr[3].splitrec(n-1);
						//	ptr[4].splitrec(n-1);
						//	ptr[5].splitrec(n-1);
						//	ptr[6].splitrec(n-1);
						//	ptr[7].splitrec(n-1);
						//}
					}

					void split(void) {
						//ptr = new Octree<T1>[8];
					}//division du cube

					void cut(void) {
						//delete[] ptr;
						//ptr=NULL;
						//node = T1();
					}// suppression des fils


					// donne le nombre de feuilles de l'octree
					auto compteextremite() -> int {

						//int indice = 0;
						//___self trac{*this};
						//trac.firstlastcube();
						//do {
						//	++indice;
						//} while (trac.nextlastcube());
						//return indice;

						return 0;
					}

			}; // class node


		public:

			// -- public lifecycle --------------------------------------------

			//octree(node& oct0)
			//: translation{} {
			//
			//	// l'avant dernière case du tableau correspond au pointeur sur la racine
			//	tab[EMAX]=&oct0;
			//
			//	// initialement le traceur est à la racine (pos = (0,0,0) et e=EMAX)
			//	e=EMAX;
			//	posxyz[0]=posxyz[1]=posxyz[2]=0;
			//
			//	// par défaut le facteur d'échelle est mis de sorte que la taille du cube racine soit égal à 1.
			//	_scale=(unsigned int)(1<<e); scale=1./_scale;
			//}

	}; // class octree

} // namespace ve




/****************************************************************************
                            classe Traceur
*****************************************************************************/


    /// Les constructeurs

//
//    inline Traceur(Octree<T>& oct0, float largeur){
//        tab[EMAX]=&oct0;// l'avant dernière case du tableau correspond au pointeur sur la racine
//        e=EMAX; posxyz[0]=posxyz[1]=posxyz[2]=0;// initialement le traceur est à la racine (pos = (0,0,0) et e=EMAX)
//        scale=largeur/(unsigned int)(1<<EMAX); _scale=1./scale;
//        translation = largeur*Vect3f(0.5,0.5,0.5);
//    }
//    // constructeur copie sans copie de la position courante du traceur.
//    inline Traceur(Traceur<T> const&t){
//        tab[EMAX]=t.tab[EMAX];// l'avant dernière case du tableau correspond au pointeur sur la racine
//        e=EMAX; posxyz[0]=posxyz[1]=posxyz[2]=0;// initialement le traceur est à la racine (pos = (0,0,0) et e=EMAX)
//        scale=t.scale; _scale=t._scale; translation = t.translation;
//    }
//
//
//
//    inline unsigned int findexposant(float valeur)const{union int_float dif; dif.f=valeur*_scale;return ((dif.i>>23)-126);}
//
//
//    /// Accesseurs et mutateurs
//
//    //inline void setscale(float echelle){scale=echelle; _scale=1./echelle;}
//    //inline void setoffset(Vect3f const&u){translation=u;}
//    inline float getscale()const{return scale;}
//    inline float getscale_()const{return _scale;}
//    inline float getlargeurtot()const{return scale*(unsigned int)(1<<EMAX);}
//    inline Vect3f getoffset()const{return translation;}
//
//    inline Octree<T>* courant()const{return tab[e];}
//    inline Octree<T>* gethead()const{return tab[EMAX];}
//    inline unsigned int getexp()const{return e;}
//    inline float getlargeur()const{return scale*(unsigned int)(1<<e);}// retourne la largeur du cube courant
//    inline float getlargeur(unsigned int e1)const{return scale*(unsigned int)(1<<e1);}// retourne la largeur du cube courant
//    inline const unsigned int* getposxyz()const{return posxyz;}// retourne un pointeur sur le tableau des coordonnées entières.
//
//    inline Vect3f getcoordonne()const{return scale*Vect3f(posxyz[0],posxyz[1],posxyz[2])-translation;}
//    // Coordonnées du coin du cube après passage à l'échelle et offset.
//
//    inline Vect3f getmiddlecoordonne()const{return scale*(Vect3f(posxyz[0],posxyz[1],posxyz[2])+(unsigned int)(1<<e)*Vect3f(0.5,0.5,0.5))-translation;}
//    // Coordonnées du milieu du cube
//
//    inline T& getnode(unsigned int e0)const{return (*tab[e0]).node;}
//    // avoir l'étiquette d'un père (il n'y a pas de vérification que le cube existe, il faut que e0>=e)
//
//    inline T& getnode()const{return (*tab[e]).node;}
//    // avoir l'étiquette du cube courant
//
//
//	/// Fonctions de recherches et d'ecriture
//
//    inline bool addposcube();
//    // incrémente le code de morton en cartésien, retourne l'indice et met l'exposant commun dans e0
//
//    void lastcube( unsigned int posx2, unsigned int posy2 , unsigned int posz2);
//    inline void lastcube(Vect3f u){u=_scale*(u+translation);  lastcube(u.x,u.y,u.z);}
//    // Positionne le traceur au cube terminal de coordonnée demandée
//
//    bool getcube( unsigned int posx2,  unsigned int posy2 , unsigned int posz2, unsigned int e0);
//    inline bool getcube(Vect3f u, unsigned int e0){u=_scale*(u+translation);  return getcube(u.x,u.y,u.z,e0);}
//    // Positionne le traceur au cube demandé si celui-ci existe, sinon, a le même effet que "lastcube"
//
//    inline Octree<T>* writeoct(Vect3f u, unsigned int e0){u=_scale*(u+translation);  return writeoct(u.x,u.y,u.z,e0);}
//    Octree<T>* writeoct( unsigned int posx2, unsigned int posy2, unsigned int posz2, unsigned int e0);
//    // si le cube n'existe pas à la position demandée, le cube est créé.
//
//    inline T& writenode(Vect3f u, unsigned int e0){u=_scale*(u+translation);  return writenode(u.x,u.y,u.z,e0);}
//    inline T& writenode( unsigned int posx2, unsigned int posy2, unsigned int posz2, unsigned int e0){
//        return  (*writeoct(posx2,posy2,posz2,e0)).node;}
//    // si le cube n'existe pas à la position demandée, le cube est créé.
//
//
//	// pour parcourir toutes les feuille
//    void firstlastcube();// initialisation avant le parcours des feuilles
//    bool nextlastcube();// va chercher la prochaine feuille
//
//    // pour parcourir touts les éléments
//    void firstcube();// initialisation avant le parcours des éléments
//    bool nextcube();// va chercher le prochain élément
//
//
//    inline void split_go(){
//        (*courant()).split();
//        tab[e-1] = (*courant()).ptr;
//        e--;
//    }/* subdivise et se place au premier fils,
//    ATTENTION : Il faut appeler cette fonction sur un cube terminal, et il faut
//    que les coordonnées soient celles du fils,
//    donc il vaut mieux utiliser cette fonction après "nextlastcube()" */
//
//
//    int set8octzone(Vect3f centrezone,float largzone, Octree<T> **oct8);// renvoie l'exposant relatif aux 8 octree.
//    /* Donne dans le tableau oct8 qui doit déjà posséder 8 cases,
//    les 8 pointeurs sur Octree englobant la zone de largeur "largzone" et de coin "coinzone".
//    Crée les éléments s'il n'y sont pas.
//    Les pointeurs obtenus peuvent être nuls si les cubes sont en dehors de l'arbre ou si la zone est contenue dans un seul cube*/
//
//    void get8oct(Vect3f milieu,float largzone, Octree<T> **oct8);
//    //void get8oct(Octree<T> **resultat,Vect3f milieu, unsigned int e0);
//    /* Donne dans le tableau resultat qui doit déjà posséder 8 cases,
//    les 8 pointeurs sur Octree entourant le vecteur "milieu" d'exposant "e0".
//    Les pointeurs obtenus peuvent être nuls si les cubes sont en dehors de l'arbre */
//
//};
//
//
///*****************************************************************
//                Méthodes de la classe Traceur
//******************************************************************/
//
//template<class T>
//inline bool Traceur<T>::addposcube(){//retourne l'indice et met l'exposant commun dans e0
//    unsigned int f1=posxyz[0] & posxyz[1] & posxyz[2];
//    //union int_float dif;
//    //dif.f=(float)((f1+(1<<e))^f1);
//    //dif.f+=.5;// pour que l'exposant ne puisse pas être négatif
//    //e = (dif.i>>23)-127;//extraction de l'exposant
//    f1>>=e;  f1=((f1+1) ^ f1)>>1;
//    while(f1){e++;f1>>=1;}
//
//    posxyz[0]>>=e;
//    posxyz[1]>>=e-1;
//    posxyz[2]>>=e-2;
//    int i = (posxyz[0] & 1)|(posxyz[1] & 2)|(posxyz[2] & 4);
//    i++;
//    posxyz[0]=((posxyz[0] & -2)|(i&1))<<e;
//    posxyz[1]=((posxyz[1] & -4)|(i&2))<<(e-1);
//    posxyz[2]=((posxyz[2] & -8)|(i&4))<<(e-2);
//
//
//
//    if(e>=EMAX){posxyz[0]=posxyz[1]=posxyz[2]=0; e=EMAX; return false;}//On termine
//    tab[e]++; // si la position est incrémentée alors le cube suivant est dans le même tableau
//    return true;
//}
//
//template<class T> void Traceur<T>::lastcube(unsigned int posx2, unsigned int posy2 , unsigned int posz2){
//    posx2 &= OCT_MASQ;
//    posy2 &= OCT_MASQ;
//    posz2 &= OCT_MASQ;
//    unsigned int difference = (posxyz[0]^posx2)|(posxyz[1]^posy2)|(posxyz[2]^posz2);
//    //*
//    difference>>=e;
//    while(difference){e++;difference>>=1;}
//    /*/
//    union int_float dif;
//    dif.f = (float)(difference | (1<<(e-1)));
//    e = (dif.i>>23)-126 ;//extraction de l'exposant
//    //*/
//    while((*tab[e]).ptr!=NULL){
//        e--;
//        int indice=((posx2>>e)&1)|(((posy2>>e)&1)<<1)|(((posz2>>e)&1)<<2);
//        tab[e] = (*tab[e+1]).ptr+indice;
//    }
//    posxyz[0]=posx2;posxyz[1]=posy2;posxyz[2]=posz2;
//}
//
//template<class T> bool Traceur<T>::getcube( unsigned int posx2, unsigned int posy2 , unsigned int posz2, unsigned int e0){
//    posx2 &= OCT_MASQ;
//    posy2 &= OCT_MASQ;
//    posz2 &= OCT_MASQ;
//    unsigned int difference = (posxyz[0]^posx2)|(posxyz[1]^posy2)|(posxyz[2]^posz2);
//    e0=min(EMAX,e0);
//    //*
//    e=max(e,e0);
//    difference>>=e;
//    while(difference){e++;difference>>=1;}
//    /*/
//    union int_float dif;
//    dif.f = (float)(difference | (((1<<e) | (1<<e0))>>1));
//    e = (dif.i>>23)-126 ;//extraction de l'exposant
//    //*/
//    while( e > e0 && (*tab[e]).ptr!=NULL){
//        e--;
//        int indice=((posx2>>e)&1)|(((posy2>>e)&1)<<1)|(((posz2>>e)&1)<<2);
//        tab[e] = (*tab[e+1]).ptr+indice;
//    }
//    posxyz[0]=posx2;posxyz[1]=posy2;posxyz[2]=posz2;
//    return e0==e;
//}
//
//template<class T> void Traceur<T>::firstlastcube(){
//    e=EMAX;
//    posxyz[0]=posxyz[1]=posxyz[2]=0;
//    while((*tab[e]).ptr!=NULL){
//        e--;
//        tab[e] = (*tab[e+1]).ptr;
//    }
//}
//template<class T> bool Traceur<T>::nextlastcube(){
//    if(!addposcube())return false;// On incrémente la position
//    while((*tab[e]).ptr!=NULL){// On prend le dernier cube
//        e--;
//        tab[e] = (*tab[e+1]).ptr;
//    }
//    return true;
//}
//template<class T> void Traceur<T>::firstcube(){e=EMAX;posxyz[0]=posxyz[1]=posxyz[2]=0;}
//template<class T> bool Traceur<T>::nextcube(){
//
//    if((*tab[e]).ptr!=NULL){//On va en profondeur
//        e--;
//        tab[e] = (*tab[e+1]).ptr;
//    }else{//on remonte et on incrémente la position
//        return addposcube();
//    }
//    return true;
//}
//template<class T>
//Octree<T>* Traceur<T>::writeoct(unsigned int posx2,unsigned int posy2,unsigned int posz2,unsigned int e0){
//    getcube(posx2,posy2,posz2,e0);
//    while(e > e0){// si l'exposant n'est pas la bon, on subdivise jusqu'à l'atteindre
//        (*courant()).split();
//        e--;
//        tab[e] = (*tab[e+1]).ptr + (((posx2>>e)&1)|(((posy2>>e)&1)<<1)|(((posz2>>e)&1)<<2));
//    }
//    return courant();
//}
//
//template<class T>
//int Traceur<T>::set8octzone(Vect3f centrezone,float largzone, Octree<T> **oct8){
//    unsigned int e0 = min(findexposant(largzone), EMAX);
//    //printf("largeur %f   ",largzone);
//    largzone = getlargeur(e0);
//    //printf("largeur supérieur %f   ",largzone);
//    //printf("largeur octree %f   \n",getlargeurtot());
//    Vect3f coinzone = centrezone - largzone*Vect3f(0.5,0.5,0.5);
//
//    //printf("test exposant %d %f %e\n",findexposant(largzone),largzone, scale);
//    if(e0 == EMAX){
//        oct8[0]=tab[EMAX];
//        oct8[1]=oct8[2]=oct8[3]=oct8[4]=oct8[5]=oct8[6]=oct8[7]=0;
//    }else{
//
//        oct8[0]=writeoct(coinzone,e0);
//        oct8[1]=writeoct(coinzone+Vect3f(largzone,0,0),e0);
//        oct8[2]=writeoct(coinzone+Vect3f(0,largzone,0),e0);
//        oct8[3]=writeoct(coinzone+Vect3f(largzone,largzone,0),e0);
//        oct8[4]=writeoct(coinzone+Vect3f(0,0,largzone),e0);
//        oct8[5]=writeoct(coinzone+Vect3f(largzone,0,largzone),e0);
//        oct8[6]=writeoct(coinzone+Vect3f(0,largzone,largzone),e0);
//        oct8[7]=writeoct(coinzone+Vect3f(largzone,largzone,largzone),e0);
//
//    }
//
//
//    return e0;
//}
//
//
//template <class T>
//void Traceur<T>::get8oct(Vect3f milieu,float largzone, Octree<T> **oct8){
//    unsigned int e0 = min(findexposant(largzone), EMAX);
//    //printf("test exposant %d %f %e\n",findexposant(largzone),largzone, scale);
//        oct8[0]=oct8[1]=oct8[2]=oct8[3]=oct8[4]=oct8[5]=oct8[6]=oct8[7]=NULL;
//
//    Vect3f coinzone = milieu - largzone*Vect3f(0.5,0.5,0.5);
//    getcube(coinzone,e0);oct8[0]=courant();
//    //*
//    getcube(coinzone+Vect3f(largzone,0,0),e0);oct8[1]=courant();
//    getcube(coinzone+Vect3f(0,largzone,0),e0);oct8[2]=courant();
//    getcube(coinzone+Vect3f(largzone,largzone,0),e0);oct8[3]=courant();
//    getcube(coinzone+Vect3f(0,0,largzone),e0);oct8[4]=courant();
//    getcube(coinzone+Vect3f(largzone,0,largzone),e0);oct8[5]=courant();
//    getcube(coinzone+Vect3f(0,largzone,largzone),e0);oct8[6]=courant();
//    getcube(coinzone+Vect3f(largzone,largzone,largzone),e0);oct8[7]=courant();
//
//    // tests pour être sur de ne
//
//
//
//    if(oct8[6]==oct8[7])oct8[7]=NULL;//égalité en x
//    if(oct8[3]==oct8[7])oct8[7]=NULL;//égalité en z
//    if(oct8[5]==oct8[7])oct8[7]=NULL;//égalité en y
//    if(oct8[4]==oct8[6])oct8[6]=NULL;//égalité en y
//    if(oct8[2]==oct8[6])oct8[6]=NULL;//égalité en z
//    if(oct8[4]==oct8[5])oct8[5]=NULL;//égalité en x
//    if(oct8[1]==oct8[5])oct8[5]=NULL;//égalité en z
//    if(oct8[0]==oct8[4])oct8[4]=NULL;//égalité en z
//    if(oct8[2]==oct8[3])oct8[3]=NULL;//égalité en x
//    if(oct8[1]==oct8[3])oct8[3]=NULL;//égalité en y
//    if(oct8[0]==oct8[2])oct8[2]=NULL;//égalité en y
//    if(oct8[0]==oct8[1])oct8[1]=NULL;//égalité en x
//    //*/
//
//
//}
//
//
//template<class T, class Fonct>
//void simplifie(Octree<T> &oct, Fonct f){
//    Traceur<T> trac(oct);
//    trac.firstcube();while(1){
//        if( (*trac.courant()).ptr != NULL ){
//            int k;
//            for(k=0;k<8;k++){
//                if( !f((*trac.courant()).ptr[k]) )break;
//            }
//
//            if(k==8){
//                (*trac.courant()).cut();
//                trac.e=min(trac.e+1,EMAX);
//            }else{
//                if(!trac.nextcube())break;
//            }
//        }else{
//            if(!trac.nextcube())break;
//        }
//    }
//}
//
///************** Une méthode de la classe Octree *****************/
//
//
//
#endif // ___void_engine_octree___
