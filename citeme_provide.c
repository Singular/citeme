/* just uncomment the following #define in order to stop providing any citation data: */

/* #define NO_CITATION_DATA */
#include <citeme.h>
#include <stdio.h>

/* _local_ library citation data */
static const CitationStruct _about =
{
  "mylib", /* SW name */
  "0.0",   /* SW version */
  "BSD",   /* SW license */
  "Oleksandr", /* SW authors */
  "\n\n\nHi, this is an example library, which wants some credits...\nHave Fun!\n\n", /* SW banner */
  "@article{CITETHIS,title={Citeme for Math. SW},year={2011},author = {O.Motsak}}" /* Bibitem */
};

/* _local_ library citation data (available via a banner) */
static const char* _banner( const BannerType _type )
{
   switch (_type)
   {
    case GetName:
    {
       return _about.name;
       break;
    }
    case GetAuthors:
    {
       return _about.authors;
       break;
    }
    case GetBannerMessage:
    {
       return _about.banner;
       break;
    }
    case GetBibItem:
    {
       return _about.bibitem;
       break;
    }
    default: 
    {
       return NULL;
       break;
    }
   }
}


/** Please call the following init function for setting things up... */
int initme()
{
   CitationError ret;

   /* case 1 */
   printf("Trying to cite with a struct: \n");

   ret = RegisterCitation(ViaStuct, &_about);

   if( ret >= Ok )
     printf("Fine citation....!\n");
   else
     printf("Bad citation.... (error code: %d)\n", ret);


   
   /* case 2 */
   printf("Trying to cite with a banner: \n");
   
   ret = RegisterCitation(ViaBanner, &_banner);
   
   if( ret >= Ok )
     printf("Fine citation....!\n");
   else
     printf("Bad citation.... (error code: %d)\n", ret);

   
   /* case 3 */
   printf("Trying to cite in some otherway: \n");
   
   ret = RegisterCitation(Otherwise);
   
   if( ret >= Ok )
     printf("Fine citation....!\n");
   else
     printf("Bad citation.... (error code: %d)\n", ret);

   return ret;
}
