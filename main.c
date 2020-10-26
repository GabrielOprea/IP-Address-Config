//Oprea-Groza Gabriel 313CB
#include <stdio.h>

#define OCTET 8 // nr de biti dintr-un octet

unsigned int build()
{
    /*Functie care citeste numere pe 8 biti cu "." intre ele
     si care concateneaza cei 4 octeti intr-o variabila pe
     32 de biti*/

    unsigned int mask = 0;
    short unsigned int byte;

    for(int i = 0 ; i < 4; i++) // nr de octeti
    {

    /* Daca e ultimul octet citit, nu va avea un caracter "."
    dupa el */ 

        if(i != 3)
            scanf("%hu.", &byte);
        else
            scanf("%hu",  &byte);

        mask = mask | (byte << (OCTET * (3 - i))); // introduc fiecare byte
    }
    
    return mask;

}

void print_bits(unsigned int IP_1)
{
    
    // Functie ce reprezinta in binar fiecare octet al unui IP
    
    unsigned int mask = 1;

    for(int j = 3; j >= 0; j--) // nr octeti
    {
    
        // impart IP-ul in bytes, prin shift-uri la stanga si la dreapta

        unsigned int byte = IP_1 << (24 - j * OCTET) >> 24;
    
        for(int i = OCTET - 1; i >= 0; i--) // nr biti per octet
        {

            mask = 1 << i; // construiesc o masca pentru a afisa bitii
            mask = byte & mask;
            
            if(mask == 0)
                printf("0");

            else
                printf("1");
        
        }

        if(j != 0) // daca nu este ultimul octet, afisez "."
            printf(".");

    }
        
        printf("\n");
    
}

int verif(unsigned int MSK_1) // verifica validitatea unei masti
{
    
    /* Inversez masca, daca e valida ar trebui sa aiba doar 0 la
    inceput si 1 la sfarsit. Observ ca un numar doar cu 1 la sfarsit
    este de forma x^2 - 1. */

    unsigned int mask = ~ MSK_1;

    mask = mask & (mask + 1);

    /* SI logic intre masca si masca marita cu 1 trebui sa fie 0,
    in caz ca e valida.*/

    if(mask == 0)
        return 1;
    else 
        return 0;

}

unsigned int repair(unsigned int MSK_1) // repar o masca nevalida
{
    
    unsigned int mask;
    unsigned int poz;

    /* inversez masca pentru a avea biti de 1 la sfarsit,
    apoi caut pozitia pentru primul 1 */

    MSK_1 = ~ MSK_1;
    for(int i = sizeof(int) * OCTET - 1; i >= 0; i--)
    {
        mask = 1 << i;
        mask = mask & MSK_1;

        if(mask != 0)
        {
            poz = i; // daca a gasit pozitia, iese fortat
            break;
        }

    }

    // de la poz in colo, transform toti bitii de 0 in biti de 1

    for(int i = poz - 1; i >= 0; i --)
    {
        mask = 1 << i;
        MSK_1 = MSK_1 | mask;
    }

    MSK_1 = ~ MSK_1; // inversez inapoi

    return MSK_1;

}

unsigned int network_address(unsigned int IP_1, int MSK_2)
{
    /*Functie care returneaza numarul obtinut din SI logic
    dintre IP_1 si MSK_2 in format zecimal*/

    unsigned int mask = 0;
    unsigned int network;

    for(int i = 31; i > 31 - MSK_2; i--)
        mask = mask | (1 << i); // construiesc MSK_2 cu biti de 1
    
    network = mask & IP_1;

    return network;

}

void print(unsigned int IP_1)
{
    /*Impart un numar pe 32 de biti in octeti prin shift-uri
    succesive la stanga si la dreapta si afisez fiecare octet*/

    printf("%u.", IP_1 >> 24);
    printf("%u.", IP_1 << OCTET >> 24);
    printf("%u.", IP_1 << OCTET * 2 >> 24);
    printf("%u",  IP_1 << OCTET * 3 >> 24);

}

void task0(unsigned int IP_1, int MSK_2)
{

    // afiseaza adresa IP_1 / MSK_2

    printf("-0 ");
    print(IP_1);
    printf("/%d\n", MSK_2);

}

void task1(int MSK_2)
{

    // afiseaza masca 2 in format zecimal

    unsigned mask = 0;
    
    printf("-1 ");
    
    for(int i = 31; i > 31 - MSK_2; i--)
        mask = mask | (1 << i); // construiesc o masca cu biti de 1
    
    print(mask); // o afisez
    printf("\n");

}

void task2(unsigned MSK_1)
{

    //Folosesc descriptorul "%o" pentru octal

    printf("-2 %o.", MSK_1 >> 24);
    printf("%o.", MSK_1 << OCTET >> 24);
    printf("%o.", MSK_1 << OCTET * 2 >> 24);
    printf("%o ", MSK_1 << OCTET * 3 >> 24);
    
    // Respectiv "%X" pentru hexadecimal (HEX)

    printf("%X.", MSK_1 >> 24);
    printf("%X.", MSK_1 << OCTET >> 24);
    printf("%X.", MSK_1 << OCTET * 2 >> 24);
    printf("%X\n",  MSK_1 << OCTET * 3 >> 24);

}

void task3(unsigned IP_1, int MSK_2)
{
    
    printf("-3 ");
    print(network_address(IP_1, MSK_2)); // afisez adresa de retea
    printf("\n");

}

void task4(unsigned IP_1, int MSK_2)
{
    
    // Afisez adresa de broadcast, cu SAU logic dintre IP si inversul mastii

    printf("-4 ");
    unsigned mask = 0;
    unsigned host;
    
    for(int i = 31; i > 31 - MSK_2; i--)
        mask = mask | (1 << i); // pun biti de 1 in masca
    
    mask = ~ mask;
    host = mask | IP_1;
    
    print(host); // afisez adresa de broadcast
    printf("\n");

}

void task5(unsigned IP_1, unsigned IP_2, int MSK_2)
{
    
    printf("-5 ");

    // compar adresele, daca ele coincid afisez "DA"
    
    if(network_address(IP_1, MSK_2) == network_address(IP_2, MSK_2))
        printf("DA\n");
    else
        printf("NU\n");

}

void task6(unsigned int MSK_1)
{
    
    printf("-6 ");

    if(verif(MSK_1)) // verific daca este valida
        printf("DA\n");
    else
        printf("NU\n");

}

void task7(unsigned int MSK_1)
{

    printf("-7 ");

    if(verif(MSK_1)) // daca e valida o afisez
        print(MSK_1);
    else
    {
        MSK_1 = repair(MSK_1); // altfel o repar, dupa o afisez
        print(MSK_1);
    }

    printf("\n");

}

void task8(unsigned int IP_1)
{
    printf("-8 ");
    print_bits(IP_1); // afisez bitii cu functia

}

void task9(unsigned int IP_2)
{
    
    unsigned int NET;     // IP-ul adresei de retea
    unsigned int MSK_N;   // Masca adresei de retea
    int NR_NET;  // numarul de retele

    printf("-9 ");
    scanf("%d", &NR_NET);
    
    for(int i = 0; i < NR_NET; i++)
    {
        
        /* Construiesc adresele pe rand, nu folosesc
        vectori pentru ca nu e eficient */

        NET = build();
        scanf("/%d", &MSK_N);

        // compar adresele de retea

        if(network_address(NET, MSK_N) == network_address(IP_2, MSK_N))
            printf("%d ", i);

    }

    printf("\n");

}

int main()
{

    int nr_seturi;
    scanf("%u", &nr_seturi); // citesc numarul de seturi de date

    for(int i = 0; i < nr_seturi; i++) // execut task-urile pentru fiecare set
    {
        
        // declar mastile si ip-urile pe 32 de biti

        unsigned int MSK_1;
        int MSK_2;
        unsigned int IP_1;
        unsigned int IP_2;

        // construiesc mastile si adresele IP din 4 octeti

        MSK_1 = build();

        scanf("%d", &MSK_2);

        IP_1 = build();

        IP_2 = build();

        // execut toate task-urile cu parametrii corespunzatori

        task0(IP_1, MSK_2);
        task1(MSK_2);
        task2(MSK_1);
        task3(IP_1, MSK_2);
        task4(IP_1, MSK_2);
        task5(IP_1, IP_2, MSK_2);
        task6(MSK_1);
        task7(MSK_1);
        task8(IP_1);
        task9(IP_2);
    }

    return 0;

}
