#include "pch.h"
#include <iostream>
#include <conio.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>

#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix)||defined(unix)||defined(unix)||defined(APPLE)||defined(MACH)
#define CLEAR "clear"
#else
#error "SO no soportado para limpiar pantalla"
#endif

using namespace System;
using namespace MySql::Data::MySqlClient;

ref struct Jugadores
{
    Int32^ id;
    String^ nombre;
    Int32^ camisola;
    String^ posicion;
    Int32^ edad;
    String^ habilidad;
    String^ piernaHabil;
    Boolean^ nacionalidad;
    String^ equpoPerteneciente;
    String^ divisionPerteneciente;
    String^ patrocinador;
    Single^ valorEnElMercado;
    Int32^ seleccionId;
};

ref struct Selecciones
{
    Int32^ id;
    String^ tecnico;
    String^ entrenadoDePorteros;
    String^ fisioterapeuta;
    String^ pais;
    String^ estadio;
    String^ area;
    Int32^ rankingFifa;
};

ref struct Encuentros
{
    Int32^ id;
    Int32^ seleciones_id;
    Int32^ visitanteId;
    String^ tipo;
    Int32^ golesLocales;
    Int32^ golesVisitantes;
    DateTime^ fecha;
    String^ estadio;

};

int main(array<System::String^>^ args)
{
    //conexion
    MySqlConnection^ conecction = gcnew MySqlConnection("datasource = localhost; username=root; password=root; database=labasededatos1");

    Console::WriteLine("1. Importar selecciones ");
    Console::WriteLine("2. Agregar una seleccion nueva ");
    Console::WriteLine("3. Importar jugadores ");
    Console::WriteLine("4. Agregar un nuevo jugador ");
    Console::WriteLine("5. Importar encuentros ");
    Console::WriteLine("6. Agregar un nuevo encuentro ");


    Int32^ selectioMenu = Int32::Parse(Console::ReadLine());



    system(CLEAR);

    switch ((int)selectioMenu)
    {
    case 1:
    {
        Console::WriteLine("Listado de selecciones ");
        MySqlCommand^ comandoSql = gcnew MySqlCommand("SELECT * FROM labasededatos1.seleciones;", conecction);
        conecction->Open();
        MySqlDataReader^ DatosSql = comandoSql->ExecuteReader();

        while (DatosSql->Read())
        {
            Console::WriteLine();
            Console::WriteLine(DatosSql->GetInt32("id"));
            Console::WriteLine(DatosSql->GetString("tecnico"));
            Console::WriteLine(DatosSql->GetString("entrenadoDePorteros"));
            Console::WriteLine(DatosSql->GetString("fisioterapeuta"));
            Console::WriteLine(DatosSql->GetString("pais"));
            Console::WriteLine(DatosSql->GetString("estadio"));
            Console::WriteLine(DatosSql->GetString("area"));
            Console::WriteLine(DatosSql->GetInt32("rankingFifa"));


        }
        conecction->Close();


        break;
    }
    case 2:
    {
        Console::WriteLine("Usted selecciono agregar una seleccion");
        Selecciones^ inputSelecction = gcnew Selecciones();

        Console::WriteLine("tecnico: ");
        inputSelecction->tecnico = Console::ReadLine();

        Console::WriteLine("Entrenador: ");
        inputSelecction->entrenadoDePorteros = Console::ReadLine();

        Console::WriteLine("Fisioterapeuta: ");
        inputSelecction->fisioterapeuta = Console::ReadLine();

        Console::WriteLine("Pais: ");
        inputSelecction->pais = Console::ReadLine();

        Console::WriteLine("Nombre del estadio : ");
        inputSelecction->estadio = Console::ReadLine();

        Console::WriteLine("area: ");
        inputSelecction->area = Console::ReadLine();

        /*string input = Console.ReadLine();
    if (!string.IsNullOrEmpty(input) )
    {
      SomeFunction(input); 
    }
*/

        do
        {

            Console::WriteLine("Solo numeros porfavor! ");
            Console::WriteLine("Ranking: ");
            inputSelecction->rankingFifa = Int32::Parse(Console::ReadLine());

        } while ((Int32)inputSelecction->rankingFifa == 0);
        
   

        if ((Int32)inputSelecction->rankingFifa == 0)//sintaxis a
        {
            Console::WriteLine("mete el dato!");//necesitare un bucle >:v

        }
        else
        {
            MySqlCommand^ comandoSql = gcnew MySqlCommand("INSERT INTO labasededatos1.seleciones (tecnico, entrenadoDePorteros, fisioterapeuta, pais, estadio, area, rankingFifa) VALUES (@entrada_tecnico, @entrada_entrenadoDePorteros, @entrada_fisioterapeuta, @entrada_pais, @entrada_estadio, @entrada_area, @entrada_rankingFifa)", conecction);

            comandoSql->Parameters->AddWithValue("entrada_tecnico", inputSelecction->tecnico);
            comandoSql->Parameters->AddWithValue("entrada_entrenadoDePorteros", inputSelecction->entrenadoDePorteros);
            comandoSql->Parameters->AddWithValue("entrada_fisioterapeuta", inputSelecction->fisioterapeuta);
            comandoSql->Parameters->AddWithValue("entrada_pais", inputSelecction->pais);
            comandoSql->Parameters->AddWithValue("entrada_estadio", inputSelecction->estadio);
            comandoSql->Parameters->AddWithValue("entrada_area", inputSelecction->area);
            comandoSql->Parameters->AddWithValue("entrada_rankingFifa", inputSelecction->rankingFifa);

            conecction->Open();
            comandoSql->ExecuteNonQuery();
            conecction->Close();
        }


        //validacion



        break;
    }

    case 3:
    {

        Console::WriteLine("Listado de jugadores");
        MySqlCommand^ comandoSql = gcnew MySqlCommand("SELECT * FROM labasededatos1.jugador", conecction);
        conecction->Open();
        MySqlDataReader^ DatosSql = comandoSql->ExecuteReader();

        while (DatosSql->Read())
        {
            Console::WriteLine();
            Console::WriteLine(DatosSql->GetInt32("id"));
            Console::WriteLine(DatosSql->GetString("nombre"));
            Console::WriteLine(DatosSql->GetInt32("camisola"));
            Console::WriteLine(DatosSql->GetString("posicion"));
            Console::WriteLine(DatosSql->GetString("edad"));
            Console::WriteLine(DatosSql->GetString("habilidad"));
            Console::WriteLine(DatosSql->GetString("piernaHabil"));
            Console::WriteLine(DatosSql->GetString("nacionalidad"));
            Console::WriteLine(DatosSql->GetString("equpoPerteneciente"));
            Console::WriteLine(DatosSql->GetString("divisionPerteneciente"));
            Console::WriteLine(DatosSql->GetString("patrocinador"));
            Console::WriteLine(DatosSql->GetFloat("valorEnElMercado"));
            Console::WriteLine(DatosSql->GetInt32("seleccionId"));

        }

        conecction->Close();

        break;
    }

    case 4:
    {
        Console::WriteLine("Usted selecciono agregar un jugador");
        Jugadores^ inputPlayers = gcnew Jugadores();

        Console::WriteLine("Nombre: ");
        inputPlayers->nombre = Console::ReadLine();

        Console::WriteLine("Numero de camisola: ");
        inputPlayers->camisola = Int32::Parse(Console::ReadLine());

        Console::WriteLine("Posicion: ");
        inputPlayers->posicion = Console::ReadLine();

        Console::WriteLine("Edad: ");
        inputPlayers->edad = Int32::Parse(Console::ReadLine());

        Console::WriteLine("Habilidades: ");
        inputPlayers->habilidad = Console::ReadLine();

        Console::WriteLine("Pierna Habil: ");
        inputPlayers->piernaHabil = Console::ReadLine();

        Console::WriteLine("true = si ; false = no ");
        Console::WriteLine("Nacionalizado: ");
        inputPlayers->nacionalidad = Boolean::Parse(Console::ReadLine());

        Console::WriteLine("Equipo perteneciente: ");
        inputPlayers->equpoPerteneciente = Console::ReadLine();

        Console::WriteLine("Division perteneciente: ");
        inputPlayers->divisionPerteneciente = Console::ReadLine();

        Console::WriteLine("Patrocinador: ");
        inputPlayers->patrocinador = Console::ReadLine();

        Console::WriteLine("Valor en Mercado: ");
        inputPlayers->valorEnElMercado = Single::Parse(Console::ReadLine());

        Console::WriteLine("ID de seleccion a la que pertenece: ");
        inputPlayers->seleccionId = Int32::Parse(Console::ReadLine());

        MySqlCommand^ comandoSql = gcnew MySqlCommand("INSERT INTO labasededatos1.jugador (nombre, camisola, posicion, edad, habilidad, piernaHabil, nacionalidad, equpoPerteneciente, divisionPerteneciente, patrocinador, valorEnElMercado, seleccionId) VALUES (@entrada_nombre, @entrada_camisola, @entrada_posicion, @entrada_edad, @entrada_habilidad, @entrada_piernaHabil, @entrada_nacionalidad, @entrada_equpoPerteneciente, @entrada_divisionPerteneciente, @entrada_patrocinador, @entrada_valorEnElMercado, @entrada_seleccionId )", conecction);

        comandoSql->Parameters->AddWithValue("entrada_nombre", inputPlayers->nombre);
        comandoSql->Parameters->AddWithValue("entrada_nro_camisola", inputPlayers->camisola);
        comandoSql->Parameters->AddWithValue("entrada_posicion", inputPlayers->posicion);
        comandoSql->Parameters->AddWithValue("entrada_edad", inputPlayers->edad);
        comandoSql->Parameters->AddWithValue("entrada_habilidades", inputPlayers->habilidad);
        comandoSql->Parameters->AddWithValue("entrada_pierna_habil", inputPlayers->piernaHabil);
        comandoSql->Parameters->AddWithValue("entrada_nacionalizado", inputPlayers->nacionalidad);
        comandoSql->Parameters->AddWithValue("entrada_equipo_perteneciente", inputPlayers->equpoPerteneciente);
        comandoSql->Parameters->AddWithValue("entrada_division_perteneciente", inputPlayers->divisionPerteneciente);
        comandoSql->Parameters->AddWithValue("entrada_patrocinador", inputPlayers->patrocinador);
        comandoSql->Parameters->AddWithValue("entrada_valor_en_mercado", inputPlayers->valorEnElMercado);
        comandoSql->Parameters->AddWithValue("entrada_selecciones_id", inputPlayers->seleccionId);

        conecction->Open();
        comandoSql->ExecuteNonQuery();
        conecction->Close();


        break;
    }


    case 5:
    {

       
        Console::WriteLine("Listado de encuentros ");
        MySqlCommand^ comandoSql = gcnew MySqlCommand("SELECT * FROM labasededatos1.encuentros", conecction);
        conecction->Open();
        MySqlDataReader^ DatosSql = comandoSql->ExecuteReader();

        while (DatosSql->Read())
        {
            Console::WriteLine();
            Console::WriteLine(DatosSql->GetInt32("id"));
            Console::WriteLine(DatosSql->GetInt32("seleciones_id"));
            Console::WriteLine(DatosSql->GetInt32("visitanteId"));
            Console::WriteLine(DatosSql->GetString("tipo"));
            Console::WriteLine(DatosSql->GetInt32("golesLocales"));
            Console::WriteLine(DatosSql->GetInt32("golesVisitantes"));
            Console::WriteLine(DatosSql->GetDateTime("fecha"));
            Console::WriteLine(DatosSql->GetString("estadio"));

        }
        conecction->Close();

        break;
    }


    case 6:
    {

        Console::WriteLine("Usted selecciono agregar un encuentro");
        Encuentros^ inputPartidos = gcnew Encuentros();

        Console::WriteLine("Id de equipo local: ");
        inputPartidos->seleciones_id = Int32::Parse(Console::ReadLine());

        Console::WriteLine("Id de equipo visitante: ");
        inputPartidos->visitanteId = Int32::Parse(Console::ReadLine());

        Console::WriteLine("Tipo de encuentro: ");
        inputPartidos->tipo = Console::ReadLine();

        Console::WriteLine("Goles locales: ");
        inputPartidos->golesLocales = Int32::Parse(Console::ReadLine());

        Console::WriteLine("Goles visitantes: ");
        inputPartidos->golesVisitantes = Int32::Parse(Console::ReadLine());

        Console::WriteLine("Formato YYYY-MM-DD 00:00:00 ");
        Console::WriteLine("Fecha del encuentro: ");
        inputPartidos->fecha = DateTime::Parse(Console::ReadLine());

        Console::WriteLine("Estadio: ");
        inputPartidos->estadio = Console::ReadLine();

        MySqlCommand^ comandoSql = gcnew MySqlCommand("INSERT INTO labasededatos1.encuentros (seleciones_id, visitanteId, tipo, golesLocales, golesVisitantes, fecha, estadio) VALUES (@entrada_seleciones_id, @entrada_visitanteId, @entrada_tipo, @entrada_golesLocales, @entrada_golesVisitantes, @entrada_fecha, @entrada_estadio)", conecction);

        comandoSql->Parameters->AddWithValue("entrada_seleciones_id", inputPartidos->seleciones_id);
        comandoSql->Parameters->AddWithValue("entrada_visitanteId", inputPartidos->visitanteId);
        comandoSql->Parameters->AddWithValue("entrada_tipo", inputPartidos->tipo);
        comandoSql->Parameters->AddWithValue("entrada_golesLocales", inputPartidos->golesLocales);
        comandoSql->Parameters->AddWithValue("entrada_golesVisitantes", inputPartidos->golesVisitantes);
        comandoSql->Parameters->AddWithValue("entrada_fecha", inputPartidos->fecha);
        comandoSql->Parameters->AddWithValue("entrada_estadio", inputPartidos->estadio);

        conecction->Open();
        comandoSql->ExecuteNonQuery();
        conecction->Close();

        break;
    }


    default:

        break;

    }

    return 0;
}