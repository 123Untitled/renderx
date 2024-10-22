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

#ifndef ___ve_config___
#define ___ve_config___


// -- builtins ----------------------------------------------------------------

#if defined(__has_builtin)
#	define ___ve_has_builtin(_) __has_builtin(_)
#else
#	define ___ve_has_builtin(_) 0
#endif


// -- attributes --------------------------------------------------------------

#if defined(__has_attribute)
#	define ___ve_has_attribute(_) __has_attribute(_)
#else
#	define ___ve_has_attribute(_) 0
#endif

#endif // ___ve_config___
