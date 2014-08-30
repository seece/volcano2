#ifndef __tstring_h
#define __tstring_h
#include <string.h>
#include <stdlib.h>

static void itoa_fake(int value, char* buf, int base) {
	// base is ignored, always 10
	sprintf(buf, "%d", value);
}

class Tstring
{
public:
    Tstring () {
        s = 0;
        Len = 0;
    }
    Tstring (char * s2) {
        s = s2;
        Len = strlen(s2);
    }
    ~Tstring () {
        if (s) delete s;
        Len = 0;
    }
    char * Str() {
        return s;
    }
    int Int() {
        if (s) {
            int i = atoi(s);
            return(i);
        }
    }
    void operator=(char *s2);
    void operator=(int num);
    void operator+(char * s2);
    void operator+(int num);
    void operator+=(Tstring s2);
private:
    char * s;
    int Len;
};
void Tstring::operator=(char *s2)
{
    if (s) delete s;
    s = s2;
    Len = strlen(s);
} // void Tstring::operator=(char *s2)
void Tstring::operator=(int num)
{
    if (s) delete s;
    char buf[20]= {0};
    itoa_fake(num, buf, 10);
    s = new char[strlen(buf)+1];

    Len = strlen(buf)+1;
    memset(s, 0, Len);
    memcpy(s, &buf, Len-1);
} // void Tstring::operator=(int num)
void Tstring::operator+(char *s2)
{
    char *s3 = new char[Len+strlen(s2)+1];
    memset(s3, 0, Len+strlen(s2)+1);
    memcpy(s3, s, Len);
    strcat(s3, s2);
    Len = strlen(s3);
    delete s;
    s = s3;
} // void Tstring::operator+(char *s2)
void Tstring::operator+(int num)
{
    char buf[20]= {0};
    itoa_fake(num, buf, 10);
    

    char *s3 = new char[Len+strlen(buf)+1];
    memset(s3, 0, Len+strlen(buf)+1);
    memcpy(s3, s, Len);
    strcat(s3, buf);
    Len = strlen(s3);
    delete s;
    s = s3;
} // void Tstring::operator+(int num)
void Tstring::operator+=(Tstring s2)
{
    char *s3 = new char[Len+strlen(s2.Str())+1];
    memset(s3, 0, Len+strlen(s2.Str())+1);
    memcpy(s3, s, Len);
    strcat(s3, s2.Str());
    Len = strlen(s3);
    delete s;
    s = s3;
} // void Tstring::operator+=(char *s2)

#endif
