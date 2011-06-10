#include <stdarg.h>
#include <stdio.h>

#include <citeme.h>

// should be visible to the outside!
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


static CitationStruct _about = { "myname", "0.0", "BSD", "Alex", "HEllo, this is my library\nMy name is ...\n Verions is ....\nHave Fun!", "...some latex code..." };

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





int main ()
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
