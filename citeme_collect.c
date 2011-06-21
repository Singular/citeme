#include <stdarg.h>
#include <stdio.h>

#include <citeme.h>
#include <citeme_lib.h>






#ifdef __cplusplus
extern "C"
{
#endif

/* CitationError RegisterCitation(const CitationType _type,...){ return Ok; } */

/**
  This global function should be visible for the outside!
 */
CitationError RegisterCitation( const CitationType _type, ... )
{
   va_list ap; 
   CitationStruct* _struct;
   BannerFunction _banner;
   CitationError retVal = Ok; 

   va_start(ap, _type);
   
   switch (_type)
   {
    case ViaStuct: 
    {
       _struct = va_arg(ap, CitationStruct*);
       printf( "%s\n", _struct->banner );
       break;
    }
    case ViaBanner:
    {
       _banner = va_arg(ap, BannerFunction);
       printf( "%s\n", (*_banner)(GetBannerMessage) );
       break;
    }
    default: 
    {
       retVal = ErrorWrongArgs;
       break;
    }
   }
   va_end(ap);
   return retVal;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */



static CitationStruct _about = { "MainApplication", "0.0", "BSD", "Oleksandr", "Hi, this is an example _main_ application,\nwhich _provides_ the RegisterCitation interface\nIt also _uses_ the example library\nHave Fun!", "...some latex code0..." };

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





static int test1()
{
   CitationError ret;
   // init citation DB.

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



int main ()
{
   int ret = 0;
   
   printf("Main banner: \n%s\n", _banner(GetBannerMessage) );

   
   printf("Setting up the main application...: \n");
   /* let's init the much _needed_ library */
   
   ret = initme(); /**< Init the data provider (used library) */
   
   
   printf("That's it!\n");
 
   return ret;
}
