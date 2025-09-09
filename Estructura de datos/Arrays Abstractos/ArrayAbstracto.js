class PersonaAbstracta {
    constructor() {
        if (new.target === PersonaAbstracta) {
            throw new Error("No se puede instanciar una clase abstracta");
        }
    }

    calcularIMC() { throw new Error("Método abstracto"); }
    esMayorDeEdad() { throw new Error("Método abstracto"); }
    mostrarInformacion() { throw new Error("Método abstracto"); }
}

class Persona extends PersonaAbstracta {
    constructor(nombre, edad, peso, altura, email = null, telefono = null) {
        super()
        this.nombre = nombre
        this.edad = edad
        this.peso = peso
        this.altura = altura
        this.email = email
        this.telefono = telefono
    }

    calcularIMC() {
        return this.peso / (this.altura * this.altura)
    }

    esMayorDeEdad() {
        return this.edad >= 18
    }

    mostrarInformacion() {
        let info = `${this.nombre}, ${this.edad} años, IMC: ${this.calcularIMC().toFixed(2)}`
        if (this.email) info += `, Email: ${this.email}`
        if (this.telefono) info += `, Tel: ${this.telefono}`
        console.log(info)
    }

    clasificarIMC() {
        const imc = this.calcularIMC()
        if (imc < 18.5) return "Bajo peso"
        else if (imc < 25) return "Normal"
        else if (imc < 30) return "Sobrepeso"
        else return "Obesidad"
    }

    getNombre() { return this.nombre }
    getEdad() { return this.edad }
    getPeso() { return this.peso }
    getAltura() { return this.altura }
    getEmail() { return this.email }
    getTelefono() { return this.telefono }

    setEdad(n) { this.edad = n }
    setPeso(n) { this.peso = n }
    setAltura(n) { this.altura = n }
}

function demostrarPersona() {
    console.log("=== Demo Persona ===")

    const p1 = new Persona("Ivan", 25, 70.5, 1.75, "elparadero@gmail.com")
    p1.mostrarInformacion()
    console.log("Mayor de edad?", p1.esMayorDeEdad() ? "Sí" : "No")
    console.log("IMC:", p1.clasificarIMC())

    const p2 = new Persona("Helmer", 17, 65, 1.68, "ivan_lizarraga@gmail.com", "123456")
    p2.mostrarInformacion()
    console.log("Mayor de edad?", p2.esMayorDeEdad() ? "Sí" : "No")

    try {
        const a = new PersonaAbstracta()
    } catch (e) {
        console.log("✓ Correcto, no se puede instanciar abstracta -", e.message)
    }
}

class PersonaSimple {
    constructor(nombre, edad, peso, altura, email = null, tel = null) {
        this.nombre = nombre
        this.edad = edad
        this.peso = peso
        this.altura = altura
        this.email = email
        this.tel = tel
    }

    calcularIMC() { return this.peso / (this.altura * this.altura) }
    esMayorDeEdad() { return this.edad >= 18 }

    mostrarInformacion() {
        let info = `${this.nombre}, ${this.edad} años, IMC: ${this.calcularIMC().toFixed(2)}`
        if (this.email) info += `, Email: ${this.email}`
        if (this.tel) info += `, Tel: ${this.tel}`
        console.log(info)
    }

    clasificarIMC() {
        const imc = this.calcularIMC()
        if (imc < 18.5) return "Bajo peso"
        else if (imc < 25) return "Normal"
        else if (imc < 30) return "Sobrepeso"
        else return "Obesidad"
    }
}

demostrarPersona()

console.log("\n=== Demo PersonaSimple ===")
const p3 = new PersonaSimple("Jesus", 30, 80, 1.80)
p3.mostrarInformacion()
console.log("IMC:", p3.calcularIMC().toFixed(2))
