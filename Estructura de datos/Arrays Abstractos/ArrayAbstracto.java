abstract class PersonaBase {
    public abstract double imc();
    public abstract boolean mayorEdad();
    public abstract void info();
}

class Persona extends PersonaBase {
    private String nom;
    private int edad;
    private double kg;
    private double mts;
    private String mail;
    private String cel;

    public Persona(String n, int e, double p, double a) {
        this(n, e, p, a, null, null);
    }

    public Persona(String n, int e, double p, double a, String m, String c) {
        nom = n;
        edad = e;
        kg = p;
        mts = a;
        mail = m;
        cel = c;
    }

    @Override
    public double imc() {
        return kg / (mts * mts);
    }

    @Override
    public boolean mayorEdad() {
        return edad >= 18;
    }

    @Override
    public void info() {
        System.out.print(nom + ", " + edad + " años, IMC: " + String.format("%.2f", imc()));
        if (mail != null) System.out.print(", Email: " + mail);
        if (cel != null) System.out.print(", Cel: " + cel);
        System.out.println();
    }

    public String estadoIMC() {
        double v = imc();
        if (v < 18.5) return "Bajo peso";
        else if (v < 25) return "Normal";
        else if (v < 30) return "Sobrepeso";
        else return "Obesidad";
    }
}

public class Main {
    public static void main(String[] args) {
        System.out.println("=== Demo Persona Java ===");

        Persona p1 = new Persona("Ivan", 25, 70.5, 1.75, "elparadero@gmail.com", null);
        p1.info();
        System.out.println("Mayor de edad? " + (p1.mayorEdad() ? "Sí" : "No"));
        System.out.println("IMC: " + p1.estadoIMC());

        Persona p2 = new Persona("Helmer", 17, 65, 1.68, "ivan_lizarraga@gmail.com", "123456");
        p2.info();
        System.out.println("Mayor de edad? " + (p2.mayorEdad() ? "Sí" : "No"));

        PersonaBase p3 = new Persona("Jesus", 30, 80, 1.80);
        p3.info();
        System.out.println("IMC calc: " + String.format("%.2f", p3.imc()));
    }
}
