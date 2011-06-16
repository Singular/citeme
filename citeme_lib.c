#include <citeme.h>

/* _local_ library citation data */
static CitationStruct _about =
{
  "citeme_lib",
  "0.0",
  "BSD",
  "Oleksandr",
  "\n=========================================================================\n"
  "Hi, this is an example library which wants some credits...\n"
  "If you want to use me, please provide the RegisterCitation global function!\n"
  "Have Fun!\n",
  "...some latex code..."
};

#include <stdio.h>

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


/** Please call the following init function for settin things up... */
int initme()
{
   CitationError ret;

   printf("Trying to cite with a struct: \n");
   ret = RegisterCitation(ViaStuct, &_about);

   if( ret >= Ok )
     printf("Fine citation....!\n");
   else
     printf("Bad citation.... (error code: %d)\n", ret);


   printf("Trying to cite with a banner: \n");
   
   ret = RegisterCitation(ViaBanner, &_banner);
   
   if( ret >= Ok )
     printf("Fine citation....!\n");
   else
     printf("Bad citation.... (error code: %d)\n", ret);

   printf("Trying to cite in some otherway: \n");
   
   ret = RegisterCitation(Otherwise);
   
   if( ret >= Ok )
     printf("Fine citation....!\n");
   else
     printf("Bad citation.... (error code: %d)\n", ret);

   return ret;
}
