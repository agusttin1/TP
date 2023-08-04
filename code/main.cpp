#include <iostream>
#include <string.h>
#include <stdio.h>
#define num_zonas 14
#define num_transportes 4
#define max_repartidores_x_zona 20

using namespace std;

struct Repartidores
{
    int documento;
    char nombre[50];
    int zona;
    int transporte;
    char patente[8];
};

int matrizRepartidores[num_zonas][num_transportes];
string transportes[num_transportes] = {"moto", "camion", "camioneta", "auto"};
int t0 = 0, t1 = 0, t2 = 0, t3 = 0;

void ordenarPorDocumento(Repartidores rp[], int numRepartidores);
bool verificarMaxZona(int zona, int transporte);
bool cargarDatos(const string &nom);
void mostrar();
void inicializarMatriz();
void transporteNoDispo(int a);
void mostrarTransporteNoDispo(int t0, int t1, int t2, int t3);
void zonaConMasRepar();

int main()
{
    bool data;
    char nombre[50];
    inicializarMatriz();
    string rutaDirectorio = "C:\\Users\\Agustin-PC\\Desktop\\K1022-Codeando-PARTE1\\archivosAdicionales\\";

    do
    {
        cout << "ingrese el nombre del archivo: ";
    cin >> nombre;

    string rutaArchivo = rutaDirectorio + string(nombre) + ".dat";
        data = cargarDatos(rutaArchivo);

        if (data)
        {
            string incorporar;
            cout << "¿Desea seguir agregando mas repartidores a otros tipos de archivos? (si/no): ";
            cin >> incorporar;

            if (incorporar == "no" || incorporar == "NO")
            {
               mostrar();
                mostrarTransporteNoDispo(t0, t1, t2, t3);
                zonaConMasRepar();
                cout << " Se ha finalizado el ingreso de repartidores. "
                     << endl;
                break;
            }
        
        }
    } while (data);
    return 0;
}

void inicializarMatriz()
{
    int i, j;
    for (i = 0; i < num_zonas; i++)
    {
        for (j = 0; j < num_transportes; j++)
        {
            matrizRepartidores[i][j] = 0;
        }
    }
}

bool cargarDatos( const string &nom)
{
    Repartidores repartidor;
    Repartidores rp[280]; // 14x20(max repartidores disponibles)

    bool var = false;
    bool checkMax;

    FILE *repar;
    repar = fopen(nom.c_str(), "ab");

    if (repar == NULL)
    {
        cout << "Error al abrir el archivo";
        return var;
    }

    cout << "Ingrese el documento del repartidor (0 para dejar de ingresar repartidor): ";
    cin >> repartidor.documento;

    int contadorRepartidores = 0; // maneja los indices del vector rp y que datos tendra cada indice, esto para poder ordenarlos mejor

    while (repartidor.documento != 0)
    {
        cout << "Ingrese el nombre y apellido del repartidor: ";
        cin.ignore(); // limpiar buffer de ENTRADA asi me toma el apellido junto con el nombre
        cin.getline(repartidor.nombre, sizeof(repartidor.nombre));

        cout << "Ingrese la zona en la que trabajara: ";
        cin >> repartidor.zona;
        cout << "Ingrese con que vehiculo trabajara: \n 0.moto \n 1.camion \n 2.camioneta \n 3.auto" << endl;
        cin >> repartidor.transporte;
        cout << "Ingrese la patente del transporte: ";
        cin >> repartidor.patente;

        transporteNoDispo(repartidor.transporte);

        checkMax = verificarMaxZona(repartidor.zona, repartidor.transporte);
        if (checkMax)
        {
            cout << "Se rechazo su inscripcion" << endl;
            break;
        }
        else
        {
            rp[contadorRepartidores] = repartidor;
            contadorRepartidores++;
            var = true;
            cout << "Ingrese el documento del repartidor (0 para dejar de ingresar repartidor): ";
            cin >> repartidor.documento;
        }
    }

    if (var)
    {
        ordenarPorDocumento(rp, contadorRepartidores);

        fwrite(&rp, sizeof(Repartidores), contadorRepartidores, repar);
    }
fclose(repar);
    return var; // retorna true cuando se ponga como documento == 0 , este valor trabaja en el main
}

void ordenarPorDocumento(Repartidores rp[], int numRepartidores)
{
    int i, j;
    for (i = 0; i < numRepartidores - 1; i++)
    {
        for (j = 0; j < numRepartidores - 1; j++)
        {
            if (rp[j].documento < rp[j + 1].documento)
            {
                Repartidores temp = rp[j];
                rp[j] = rp[j + 1];
                rp[j + 1] = temp;
            }
        }
    }
}

bool verificarMaxZona(int zona, int transporte)
{

    bool check = false;
    if ((zona >= 1 && zona <= num_zonas) && (transporte >= 0 && transporte < num_transportes))
    {
        if (matrizRepartidores[zona - 1][transporte] < max_repartidores_x_zona)
        {
            matrizRepartidores[zona - 1][transporte]++;
            cout << "Repartidor agregado en zona"
                << " " << zona << ", transporte " << transportes[transporte] << endl;
        }
        else
        {
            cout << "la zona"
                << " " << zona << "con transporte "
                << " " << transportes[transporte] << " "
                << " ha alcanzado el maximo de repartidores. " << endl;
            check = true;
        }
    }
    else
    {
        cout << "Datos invalidos.";
        check = true;
    }

    return check;
}

void mostrar()
{

    cout << "Cantidad de repartidores por zona y transporte: " << endl;
    for (int i = 0; i < num_zonas; i++)
    {
        for (int j = 0; j < num_transportes; j++)
        {
            cout << "Zona " << i + 1 << "," << transportes[j] << ":" << matrizRepartidores[i][j] << endl;
        }
    }
}

void transporteNoDispo(int a)
{
    if (a == 0)
    {
        t0++;
    }
    else if (a == 1)
    {
        t1++;
    }
    else if (a == 2)
    {
        t2++;
    }
    else if (a == 3)
    {
        t3++;
    }
}

void mostrarTransporteNoDispo(int t0, int t1, int t2, int t3)
{

    if (t0 == 0)
    {
        cout << "Los medios de transporte no disponibles son: " << transportes[0] << endl;
    }
    if (t1 == 0)
    {
        cout << "Los medios de transporte no disponibles son: " << transportes[1] << endl;
    }
    if (t2 == 0)
    {
        cout << "Los medios de transporte no disponibles son: " << transportes[2] << endl;
    }
    if (t3 == 0)
    {
        cout << "Los medios de transporte no disponibles son: " << transportes[3] << endl;
    }

    if(t0 != 0 && t1 !=0 && t2 != 0 && t3 != 0){
        cout<<"Todos los medios de transportes estan disponibles."<<endl;
    }
}

void zonaConMasRepar()
{
    int i, j;
    int maxRepartidores = 0;
    int zonaMasRepartidores = 1;
    for (i = 0; i < num_zonas; i++)
    {
        int contador = 0;

        for (j = 0; j < num_transportes; j++)
        {
            contador = contador + matrizRepartidores[i][j];
        }
        if (contador > maxRepartidores)
        {
            maxRepartidores = contador;
            zonaMasRepartidores = i + 1;
        }
    }

    if (maxRepartidores > 0)
    {
        cout << "La zona con mas repartidores anotados es: " << zonaMasRepartidores << endl;
        cout << "La cantidad de repartidores en la zona " << zonaMasRepartidores << ", es " << maxRepartidores << endl;
    }
    else
    {
        cout << "No se encontraron zonas con repartidores." << endl;
    }
}
