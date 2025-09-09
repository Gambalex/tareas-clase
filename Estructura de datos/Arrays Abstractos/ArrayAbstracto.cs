using System;

namespace Demo
{
    // Clase abstracta base
    public abstract class Base
    {
        public abstract double Imc();
        public abstract bool Mayor();
        public abstract void Info();
    }

    // Clase concreta
    public class Persona : Base
    {
        private string nom;
        private int edad;
        private double kg;
        private double mts;
        private string mail;
        private string cel;

        public Persona(string nom, int edad, double kg, double mts, string mail = null, string cel = null)
        {
            this.nom = nom;
            this.edad = edad;
            this.kg = kg;
            this.mts = mts;
            this.mail = mail;
            this.cel = cel;
        }

        public override double Imc() => kg / (mts * mts);

        public override bool Mayor() => edad >= 18;

        public override void Info()
        {
            Console.Write($"{nom}, {edad} años, IMC: {Imc():F2}");
            if (!string.IsNullOrEmpty(mail)) Console.Write($", Email: {mail}");
            if (!string.IsNullOrEmpty(cel)) Console.Write($", Cel: {cel}");
            Console.WriteLine();
        }

        public string Clasificar()
        {
            double v = Imc();
            if (v < 18.5) return "Bajo peso";
            else if (v < 25) return "Normal";
            else if (v < 30) return "Sobrepeso";
            else return "Obesidad";
        }
    }

    class App
    {
        static void Main(string[] args)
        {
            Console.WriteLine("=== Demo Persona en C# ===");

            Persona p1 = new Persona("Ivan", 25, 70.5, 1.75, "ivan@mail.com");
            p1.Info();
            Console.WriteLine("¿Mayor de edad? " + (p1.Mayor() ? "Sí" : "No"));
            Console.WriteLine("Clasificación IMC: " + p1.Clasificar());
        }
    }
}
