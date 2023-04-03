public class CiclosUtilidades
{
    public static void MostrarCiclo(
      List<PresionArterialRecord> ciclo,
      out decimal valorMinimo,
      out decimal valorMaximo
    )
    {
        valorMaximo = 0;
        valorMinimo = 9999;

        foreach (var presion in ciclo)
        {
            valorMinimo = presion.Presion < valorMinimo ? presion.Presion : valorMinimo;
            valorMaximo = presion.Presion > valorMaximo ? presion.Presion : valorMaximo;
            Console.Write(presion.Presion.ToString().PadRight(12) + "| ");
        }
    }
}
