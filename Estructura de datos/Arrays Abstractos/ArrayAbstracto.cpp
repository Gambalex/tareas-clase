#include <iostream>
#include <string>
#include <optional>
#include <memory>
#include <iomanip>

class PersonaBase {
public:
    virtual ~PersonaBase() = default;
    virtual double imc() const = 0;
    virtual bool mayorEdad() const = 0;
    virtual void info() const = 0;
};

class Persona : public PersonaBase {
private:
    std::string nom;
    int edad;
    double kg;
    double mts;
    std::optional<std::string> correo;
    std::optional<std::string> cel;

public:
    Persona(std::string n, int e, double p, double a,
            std::optional<std::string> mail = std::nullopt,
            std::optional<std::string> t = std::nullopt)
        : nom(std::move(n)), edad(e), kg(p), mts(a), correo(std::move(mail)), cel(std::move(t)) {}

    double imc() const override { return kg / (mts * mts); }
    bool mayorEdad() const override { return edad >= 18; }

    void info() const override {
        std::cout << nom << ", " << edad << " años, IMC: "
                  << std::fixed << std::setprecision(2) << imc();
        if (correo) std::cout << ", Email: " << *correo;
        if (cel) std::cout << ", Cel: " << *cel;
        std::cout << "\n";
    }

    std::string estadoIMC() const {
        double v = imc();
        if (v < 18.5) return "Bajo peso";
        else if (v < 25) return "Normal";
        else if (v < 30) return "Sobrepeso";
        else return "Obesidad";
    }

    void setEdad(int e) { edad = e; }
    void setPeso(double p) { kg = p; }
    void setAltura(double a) { mts = a; }
};

void probar() {
    std::cout << "=== Demo Persona ===\n";

    Persona p1("Ivan", 25, 70.5, 1.75, "elparadero@gmail.com");
    p1.info();
    std::cout << "Mayor? " << (p1.mayorEdad() ? "Sí" : "No") << "\n";
    std::cout << "IMC: " << p1.estadoIMC() << "\n";

    Persona p2("Helmer", 17, 65, 1.68, "ivan_lizarraga@gmail.com", "123456");
    p2.info();
    std::cout << "Mayor? " << (p2.mayorEdad() ? "Sí" : "No") << "\n";
}

void probarSmart() {
    std::unique_ptr<PersonaBase> per = std::make_unique<Persona>("Jesus", 30, 80, 1.80);
    per->info();
    std::cout << "IMC calc: " << per->imc() << "\n";
}

int main() {
    probar();
    std::cout << "\n=== Con SmartPointers ===\n";
    probarSmart();
    return 0;
}
