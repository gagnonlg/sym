/*
 *  © 2013 Louis-Guillaume Gagnon <louis.guillaume.gagnon@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

#define NPAIRS 39

char pairs[NPAIRS][2] =
{
    {'8','8'},
    {'A','A'},
    {'b','d'},
    {'d','b'},
    {'H','H'},
    {'i','i'},
    {'I','I'},
    {'m','m'},
    {'M','M'},
    {'o','o'},
    {'O','O'},
    {'p','q'},
    {'q','p'},
    {'T','T'},
    {'U','U'},
    {'v','v'},
    {'V','V'},
    {'x','x'},
    {'X','X'},
    {'Y','Y'},
    {'!','!'},
    {'^','^'},
    {'*','*'},
    {'(',')'},
    {')','('},
    {'-','-'},
    {'_','_'},
    {'+','+'},
    {'=','='},
    {'{','}'},
    {'}','{'},
    {'[',']'},
    {']','['},
    {':',':'},
    {'\\','/'},
    {'/','\\'},
    {'>','<'},
    {'<','>'},
    {'.','.'}
};
    
uint32_t randInt() 
{
    int urand;
    uint32_t r;

    urand = open("/dev/urandom",O_RDONLY);
    read(urand, &r, sizeof(r));
    close(urand);

    return r;
}

char lookup(char c)
{
    char c2;
    
    for(int i = 0; i < NPAIRS; i++) 
    {
        if(c == pairs[i][0]) {
            c2 = pairs[i][1];
            break;
        }
    }
    return c2;
}

char randchar()
{
    uint32_t i = randInt() % NPAIRS;
    return pairs[i][0];
}



void reverse(char *str)
{
    int len;

    len = strlen(str);

    for(int i = 0; i < len/2; i++) {
        str[i]           ^= str[len - i - 1];
        str[len - i - 1] ^= str[i];
        str[i]           ^= str[len - i - 1];
    }
}  
        
char* mirror(char *str)
{
    int len;
    char *str2;    

    len = strlen(str);
    str2 = malloc(sizeof(char)*len + 1);

    for(int i = 0; i < len; i++)
        str2[i] = lookup(str[i]);

    str2[len] = '\0';

    reverse(str2);

    return str2;
}

char* strgen(int len)
{
    char *str;

    str = malloc(sizeof(char)*len + 1);
    
    for(int i = 0; i < len; i++) 
        str[i] = randchar();

    str[len] = '\0'; 

    return str;
}

int main(void)
{
    char *str,*str2;
    uint32_t len;    


    len = (randInt() % 10) + 1;
    
    str  = strgen(len);
    str2 = mirror(str);

    printf("%s%s\n",str,str2);

    return 0;
}


