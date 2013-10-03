
/* SWISSEPH
 * $Header: /home/dieter/sweph/RCS/swedll.h,v 1.75 2009/04/08 07:19:08 dieter Exp $
 *
 *  Windows DLL interface imports for the Astrodienst SWISSEPH package
 *

**************************************************************/  

/* Copyright (C) 1997 - 2008 Astrodienst AG, Switzerland.  All rights reserved.

  License conditions
  ------------------

  This file is part of Swiss Ephemeris.

  Swiss Ephemeris is distributed with NO WARRANTY OF ANY KIND.  No author
  or distributor accepts any responsibility for the consequences of using it,
  or for whether it serves any particular purpose or works at all, unless he
  or she says so in writing.  

  Swiss Ephemeris is made available by its authors under a dual licensing
  system. The software developer, who uses any part of Swiss Ephemeris
  in his or her software, must choose between one of the two license models,
  which are
  a) GNU public license version 2 or later
  b) Swiss Ephemeris Professional License

  The choice must be made before the software developer distributes software
  containing parts of Swiss Ephemeris to others, and before any public
  service using the developed software is activated.

  If the developer choses the GNU GPL software license, he or she must fulfill
  the conditions of that license, which includes the obligation to place his
  or her whole software project under the GNU GPL or a compatible license.
  See http://www.gnu.org/licenses/old-licenses/gpl-2.0.html

  If the developer choses the Swiss Ephemeris Professional license,
  he must follow the instructions as found in http://www.astro.com/swisseph/ 
  and purchase the Swiss Ephemeris Professional Edition from Astrodienst
  and sign the corresponding license contract.

  The License grants you the right to use, copy, modify and redistribute
  Swiss Ephemeris, but only under certain conditions described in the License.
  Among other things, the License requires that the copyright notices and
  this notice be preserved on all copies.

  Authors of the Swiss Ephemeris: Dieter Koch and Alois Treindl

  The authors of Swiss Ephemeris have no control or influence over any of
  the derived works, i.e. over software or services created by other
  programmers which use Swiss Ephemeris functions.

  The names of the authors or of the copyright holder (Astrodienst) must not
  be used for promoting any software, product or service which uses or contains
  the Swiss Ephemeris. This copyright notice is the ONLY place where the
  names of the authors can legally appear, except in cases where they have
  given special permission in writing.

  The trademarks 'Swiss Ephemeris' and 'Swiss Ephemeris inside' may be used
  for promoting such software, products or services.
*/ 
    

/* $Id: swedll.h,v 1.75 2009/04/08 07:19:08 dieter Exp $ */ 
    
#ifdef __cplusplus
extern "C"
{
    
#endif                          /* 
#ifndef _SWEDLL_H
#define _SWEDLL_H
    
#ifndef _SWEPHEXP_INCLUDED   
#include "swephexp.h"
#endif                          /* 
    
#ifdef USE_DLL16 /* 16bit DLL */
#define DllImport extern 
#else                           /* 
#ifdef __cplusplus
#define DllImport extern "C" __declspec( dllimport )
#else                           /* 
#define DllImport  __declspec( dllimport )
#endif                          /* 
#endif                          /* 
    
                                                double *geopos, double *datm,
                                                double *dobs,
                                                char *ObjectName,
                                                int32 TypeEvent, int32 iflag,
                                                double *dret, char *serr);
     
                                                       double *geopos,
                                                       double *datm,
                                                       double *dobs,
                                                       char *ObjectName,
                                                       int32 TypeEvent,
                                                       int32 helflag,
                                                       double *darr,
                                                       char *serr);
     
                                                   double *geopos,
                                                   double *datm, double *dobs,
                                                   char *ObjectName,
                                                   int32 helflag,
                                                   double *dret, char *serr);
     

/* the following are secret, for Victor Reijs' */ 
      DllImport int32 FAR PASCAL swe_heliacal_angle(double tjdut,
                                                    double *dgeo,
                                                    double *datm,
                                                    double *dobs,
                                                    int32 helflag, double mag,
                                                    double azi_obj,
                                                    double azi_sun,
                                                    double azi_moon,
                                                    double alt_moon,
                                                    double *dret, char *serr);
     
                                                         double *dgeo,
                                                         double *datm,
                                                         double *dobs,
                                                         int32 helflag,
                                                         double mag,
                                                         double azi_obj,
                                                         double alt_obj,
                                                         double azi_sun,
                                                         double azi_moon,
                                                         double alt_moon,
                                                         double *dret,
                                                         char *serr);
    
    
    
                                          
    
                                             int32 iflag, 
                                             
    
                                             int32 iflag, 
                                             
    
                                                int32 iflag, 
                                                
    
                                                 char *serr);
    
                                               double nut);
     
    
    
                                          double geolon, int hsys,
                                          
    
                                             double geolat, double geolon,
                                             int hsys, 
                                             double *ascmc);
    
                                               double eps, int hsys,
                                               
                                               double *ascmc);
    
                                                double eps, int hsys,
                                                double *xpin, char *serr);
    
                                                      char *starname,
                                                      int32 iflag,
                                                      int32 imeth,
                                                      double *geopos,
                                                      double atpress,
                                                      double attemp,
                                                      double *dgsect,
                                                      char *serr);
    
                                                 double ayan_t0);
    
    
    
    
                                                   double utime, /* universal time in hours (decimal) */ 
                                                   char c, /* calendar g[regorian]|j[ulian]|a[stro = greg] */ 
                                                   double *tjd);
    
                                             
    
                                           
                                           
    
                                                  int32 iday, 
                                                  int32 imin, double dsec,
                                                  
                                                  
                                                  int32 * imonth_out,
                                                  int32 * iday_out,
                                                  
                                                  int32 * imin_out,
                                                  double *dsec_out);
    
                                               int32 iday, 
                                               int32 imin, double dsec,
                                               
                                               char *serr);
    
                                                int32 gregflag,
                                                
                                                int32 * imonth, int32 * iday,
                                                
                                                double *dsec);
    
                                                 int32 gregflag,
                                                 
                                                 int32 * imonth, int32 * iday,
                                                 
                                                 double *dsec);
    
                                            char *serr);
    
     
     
     
     
     
     
                                            double eps);
     
                                               double eps);
    
                                             double height);
    

/**************************** 
 * from swecl.c 
 ****************************/ 
     

/* computes geographic location and attributes of solar 
 * eclipse at a given tjd */ 
      DllImport int32 FAR PASCAL swe_sol_eclipse_where(double tjd, int32 ifl,
                                                       double *geopos,
                                                       double *attr,
                                                       char *serr);
    
                                                      char *starname,
                                                      int32 ifl,
                                                      double *geopos,
                                                      double *attr,
                                                      char *serr);
    

/* computes attributes of a solar eclipse for given tjd, geolon, geolat */ 
      DllImport int32 FAR PASCAL swe_sol_eclipse_how(double tjd, int32 ifl,
                                                     double *geopos,
                                                     double *attr,
                                                     char *serr);
    

/* finds time of next local eclipse */ 
      DllImport int32 FAR PASCAL swe_sol_eclipse_when_loc(double tjd_start,
                                                          int32 ifl,
                                                          double *geopos,
                                                          double *tret,
                                                          double *attr,
                                                          int32 backward,
                                                          char *serr);
    
                                                         int32 ipl,
                                                         char *starname,
                                                         int32 ifl,
                                                         double *geopos,
                                                         double *tret,
                                                         double *attr,
                                                         int32 backward,
                                                         char *serr);
    

/* finds time of next eclipse globally */ 
      DllImport int32 FAR PASCAL swe_sol_eclipse_when_glob(double tjd_start,
                                                           int32 ifl,
                                                           int32 ifltype,
                                                           double *tret,
                                                           int32 backward,
                                                           char *serr);
    

/* finds time of next occultation globally */ 
      DllImport int32 FAR PASCAL swe_lun_occult_when_glob(double tjd_start,
                                                          int32 ipl,
                                                          char *starname,
                                                          int32 ifl,
                                                          int32 ifltype,
                                                          double *tret,
                                                          int32 backward,
                                                          char *serr);
    

/* computes attributes of a lunar eclipse for given tjd */ 
      DllImport int32 FAR PASCAL swe_lun_eclipse_how(
                                                     
                                                     
                                                     
                                                     
     
                                                      int32 ifl,
                                                      int32 ifltype,
                                                      double *tret,
                                                      int32 backward,
                                                      char *serr);
    

/* planetary phenomena */ 
      DllImport int32 FAR PASCAL swe_pheno(double tjd, int32 ipl, int32 iflag,
                                           
    
                                              int32 iflag, double *attr,
                                              char *serr);
    
                                             double attemp, int32 calc_flag);
     
                                                      double geoalt,
                                                      double atpress,
                                                      double attemp,
                                                      double lapse_rate,
                                                      int32 calc_flag,
                                                      double *dret);
     
    
                                          
                                          
                                          
    
                                              
                                              
                                              
    
                                                char *starname,
                                                
                                                
                                                
                                                double attemp, 
                                                
    
                                                         int32 ipl,
                                                         char *starname,
                                                         
                                                         int32 rsmi,
                                                         
                                                         
                                                         double attemp,
                                                         
                                                         
                                                         
    
                                             int32 iflag, 
                                             
                                             
                                             
    
                                                int32 iflag, 
                                                
                                                
                                                
    

/*DllImport int32 FAR PASCAL HeliacalAngle(double Magn, double Age, int SN, double AziO, double AltM, double AziM, double JDNDaysUT, double AziS, double Lat, double HeightEye, double Temperature, double Pressure, double RH, double VR, double *dangret, char *serr);

DllImport int32 FAR PASCAL HeliacalJDut(double JDNDaysUTStart, double Age, int SN, double Lat, double Longitude, double HeightEye, double Temperature, double Pressure, double RH, double VR, char *ObjectName, int TypeEvent, char *AVkind, double *dret, char *serr);*/ 
     

/******************************************************* 
 * other functions from swephlib.c;
 * they are not needed for Swiss Ephemeris,
 * but may be useful to former Placalc users.
 ********************************************************/ 
     

/* normalize argument into interval [0..DEG360] */ 
      DllImport centisec FAR PASCAL swe_csnorm(centisec p);
    

/* distance in centisecs p1 - p2 normalized to [0..360[ */ 
      DllImport centisec FAR PASCAL swe_difcsn(centisec p1, centisec p2);
    
    

/* distance in centisecs p1 - p2 normalized to [-180..180[ */ 
      DllImport centisec FAR PASCAL swe_difcs2n(centisec p1, centisec p2);
    
    
     
     
     
    

/* round second, but at 29.5959 always down */ 
      DllImport centisec FAR PASCAL swe_csroundsec(centisec x);
    

/* double to int32 with rounding, no overflow check */ 
      DllImport int32 FAR PASCAL swe_d2l(double x);
    
                                              int32 * ideg, int32 * imin,
                                              int32 * isec, double *dsecfr,
                                              int32 * isgn);
    

/* monday = 0, ... sunday = 6 */ 
      DllImport int FAR PASCAL swe_day_of_week(double jd);
    
                                                AS_BOOL suppressZero,
                                                char *a);
    
                                                  char mchar, char *s);
    
    

/* additional functions for antiquated GFA basic DLL interface.
 * double -> double *
 * char   -> char *
 * void   -> int
 */ 
     
                                            int32 iflag, 
                                            
    
                                               int32 iflag, 
                                               
    
                                               int32 iflag, 
                                               
    
                                                  int32 iflag, 
                                                  
    
    
    
    
    
    
                                              
     
    
                                                  double *ayan_t0);
    
                                                  double *ayan);
     
                                                     double *ayan);
    
                                             double *eps);
     
                                                double *eps);
    
                                              double *height);
    
     
    
    
                                                     double *utime, /* universal time in hours (decimal) */ 
                                                     char *c, /* calendar g[regorian]|j[ulian]|a[stro = greg] */ 
                                                     double *tjd);
    
                                            double *hour, 
                                            double *tjd);
    
                                            
                                            double *jut);
    
                                            double *geolon, int hsys,
                                            
    
                                               double *geolat, double *geolon,
                                               int hsys, 
                                               double *ascmc);
    
                                                 double *geolat, double *eps,
                                                 int hsys, 
                                                 double *ascmc);
    
                                               double *eps, int hsys,
                                               double *xpin, double *hpos,
                                               char *serr);
    

/* normalize argument into interval [0..DEG360] */ 
      DllImport centisec FAR PASCAL swe_csnorm_d(centisec p);
    

/* distance in centisecs p1 - p2 normalized to [0..360[ */ 
      DllImport centisec FAR PASCAL swe_difcsn_d(centisec p1, centisec p2);
    
                                             double *diff);
    

/* distance in centisecs p1 - p2 normalized to [-180..180[ */ 
      DllImport centisec FAR PASCAL swe_difcs2n_d(centisec p1, centisec p2);
    
                                              double *diff);
    

/* round second, but at 29.5959 always down */ 
      DllImport centisec FAR PASCAL swe_csroundsec_d(centisec x);
    

/* double to int32 with rounding, no overflow check */ 
      DllImport int32 FAR PASCAL swe_d2l_d(double *x);
    
                                               int32 * ideg, int32 * imin,
                                               int32 * isec, double *dsecfr,
                                               int32 * isgn);
    

/* monday = 0, ... sunday = 6 */ 
      DllImport int FAR PASCAL swe_day_of_week_d(double *jd);
    
                                                  AS_BOOL suppressZero,
                                                  char *a);
    
                                                    char *mchar, char *s);
    
    

/**************************** 
 * from swecl.c 
 ****************************/ 
     

/* computes geographic location and attributes of solar 
 * eclipse at a given tjd */ 
      DllImport int32 FAR PASCAL swe_sol_eclipse_where_d(double *tjd_ut,
                                                         int32 ifl,
                                                         double *geopos,
                                                         double *attr,
                                                         char *serr);
    

/* computes attributes of a solar eclipse for given tjd, geolon, geolat */ 
      DllImport int32 FAR PASCAL swe_sol_eclipse_how_d(double *tjd_ut,
                                                       int32 ifl,
                                                       double geolon,
                                                       double geolat,
                                                       double geohgt,
                                                       double *attr,
                                                       char *serr);
    

/* finds time of next local eclipse */ 
      DllImport int32 FAR PASCAL swe_sol_eclipse_when_loc_d(double *tjd_start,
                                                            int32 ifl,
                                                            double *geopos,
                                                            double *tret,
                                                            double *attr,
                                                            AS_BOOL backward,
                                                            char *serr);
    

/* finds time of next eclipse globally */ 
      DllImport int32 FAR PASCAL swe_sol_eclipse_when_glob_d(double
                                                             *tjd_start,
                                                             int32 ifl,
                                                             int32 ifltype,
                                                             
                                                             AS_BOOL backward,
                                                             char *serr);
    

/* computes attributes of a lunar eclipse for given tjd */ 
      DllImport int32 FAR PASCAL swe_lun_eclipse_how_d(
                                                       
                                                       
                                                       
     
                                                        int32 ifl,
                                                        int32 ifltype,
                                                        
                                                        AS_BOOL backward,
                                                        char *serr);
    
                                             int32 iflag, 
                                             char *serr);
    
                                                int32 iflag, double *attr,
                                                char *serr);
    
                                            double *attemp, int32 calc_flag,
                                            double *retalt);
    
                                           
                                           
                                           
    
                                               
                                               
                                               
    
                                                  char *starname,
                                                  
                                                  
                                                  
                                                  double *attemp,
                                                  
    
                                               int32 iflag, 
                                               
                                               
                                               
    
                                                  int32 iflag, 
                                                  
                                                  double *xndsc,
                                                  
                                                  double *xaphe, 
    
#endif  /* !_SWEDLL_H */
#ifdef __cplusplus
} /* extern C */ 
#endif                          /* 