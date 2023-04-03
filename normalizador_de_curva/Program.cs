// See https://aka.ms/new-console-template for more information
using System.Globalization;
using CsvHelper;

var ciclos = new List<List<PresionArterialRecord>>();
const int presionMinima = 85;

using (var reader = new StreamReader("data/data.csv"))
using (var csv = new CsvReader(reader, CultureInfo.InvariantCulture))
{
    var records = csv.GetRecords<PresionArterialRecord>().ToList();
    var cicloActual = new List<PresionArterialRecord>();
    decimal valorAnterior = 0;
    var estaEsperandoPrincipioDeCiclo = true;
    foreach (var presion in records)
    {
        var estaSubiendo = presion.Presion > valorAnterior;
        if (estaSubiendo && presion.Presion < presionMinima && estaEsperandoPrincipioDeCiclo)
        {
            ciclos.Add(cicloActual);
            cicloActual = new();
            estaEsperandoPrincipioDeCiclo = false;
        }

        if (presion.Presion > presionMinima)
        {
            estaEsperandoPrincipioDeCiclo = true;
        }
        cicloActual.Add(presion);
        valorAnterior = presion.Presion;
    }
}

/*
var cicloConDiferenciaMasCercana = ciclos[0];
decimal diferenciaMasExacta = 4;
const decimal diferenciaDeseadaExacta = 40;
var index = 1;

foreach (var ciclo in ciclos)
{
    Console.WriteLine($"Ciclo: {index}");

    MostrarCiclo(ciclo, out var valorMinimo, out var valorMaximo);
    index++;
    var diferencia = valorMaximo - valorMinimo;
    decimal diferenciaAbsoluta = Math.Abs(diferencia - diferenciaDeseadaExacta);
    if (diferenciaAbsoluta < diferenciaMasExacta)
    {
        cicloConDiferenciaMasCercana = ciclo;
        diferenciaMasExacta = diferenciaAbsoluta;
    }

    Console.WriteLine($"\nValor minimo: {valorMinimo} valorMaximo: {valorMaximo}");
    Console.WriteLine($"Diferencia: {diferencia}, Absoluta {diferenciaAbsoluta}");
    Console.WriteLine();
}
*/

var cicloPoderoso = ciclos[108];
CiclosUtilidades.MostrarCiclo(ciclos[108], out var valorMinimo, out var valorMaximo);
Console.WriteLine($"\n{valorMinimo}|{valorMaximo}");
var valorMaximoAjustado = valorMaximo - valorMinimo;
foreach (var presion in cicloPoderoso)
{
    presion.Presion -= valorMinimo;
    presion.Presion /= valorMaximoAjustado;
}

CiclosUtilidades.MostrarCiclo(cicloPoderoso, out var _valorMinimo, out var _valorMaximo);

Console.WriteLine($"Numero de pasos: {cicloPoderoso.Count()}");
Console.WriteLine();
foreach (var presion in cicloPoderoso)
{
    Console.Write($"{float.Parse(presion.Presion.ToString())}, ");
}
