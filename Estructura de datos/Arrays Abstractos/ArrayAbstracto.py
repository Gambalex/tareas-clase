from abc import ABC, abstractmethod
from dataclasses import dataclass
from typing import Optional

class Base(ABC):
    @abstractmethod
    def imc(self) -> float:
        pass
    
    @abstractmethod
    def mayor(self) -> bool:
        pass

@dataclass
class Persona(Base):
    nom: str
    edad: int
    kg: float
    mts: float
    mail: Optional[str] = None
    cel: Optional[str] = None

    def imc(self) -> float:
        return self.kg / (self.mts ** 2)
    
    def mayor(self) -> bool:
        return self.edad >= 18
    
    def __str__(self) -> str:
        return f"{self.nom}, {self.edad} años, IMC: {self.imc():.2f}"

# Uso
p1 = Persona("Ivan", 25, 70.5, 1.75, "ivan@mail.com")
print(p1)
print("Mayor de edad?", p1.mayor())
