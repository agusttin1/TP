#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

struct Repar
{
    int documento;
    char nombre[50];
    int zona;
    int transporte;
    char patente[8];
};

int main()
{
    FILE *arch;
    arch = fopen("C:\\Users\\Agustin-PC\\Desktop\\K1022-Codeando-PARTE1\\archivosAdicionales\\Auto.dat", "rb");
    if (arch == NULL)
    {
        cout << "Error al abrir el archivo";
    }
    else
    {
        Repar r;
        while (fread(&r, sizeof(r), 1, arch) > 0)
        {
            cout << "Nombre y Apellido: " << r.nombre << ", Documento: " << r.documento << ", codigo de transporte: " << r.transporte << ", zona: " << r.zona << ", patente: " << r.patente << endl;
        }

        fclose(arch);
    }
    return 0;
}
