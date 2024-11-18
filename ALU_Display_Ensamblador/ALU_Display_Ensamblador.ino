char data[26];
int bits_obt;

void setup() {
  Serial.begin(9600);
  Serial.println("En línea, esperando instrucciones...");
  Serial.print("Ingrese la operación deseada: ");
  Serial.println("SUM, RES, MUL, DIV");
  Serial.println("AND, OR, NOT, XOR, NOR, XNOR, NAND");
}

void loop() {
  while (Serial.available()) {
    bits_obt = Serial.readBytesUntil(13, data, 25);  // Lee hasta 25 bytes o hasta que encuentre <CR> (13)
    data[bits_obt] = 0;                              // Agrega un terminador 0 al final de la cadena
    
    Serial.print("Instrucción recibida: ");
    Serial.println(data);

    // Operación de Suma
    bool mnemonic0 = strcmp(data, "SUM");
    if (!mnemonic0) {
      limpiarDisplay();
      int a = solicitarNumero("Digita el primer número: ");
      int b = solicitarNumero("Digita el segundo número:");
      int r = a + b;

      Serial.println("El resultado es:");
      Serial.println(r);
      mostrarResultado(r);
      Serial.println("Suma realizada");
    }

    // Operación de Resta
    bool mnemonic1 = strcmp(data, "RES");
    if (!mnemonic1) {
      limpiarDisplay();
      int a = solicitarNumero("Digita el primer número:");
      int b = solicitarNumero("Digita el segundo número:");
      int r = a - b;

      Serial.println("El resultado es:");
      Serial.println(r);
      mostrarResultado(r);
      Serial.println("Resta realizada");
    }

    // Operación de Multiplicación
    bool mnemonic2 = strcmp(data, "MUL");
    if (!mnemonic2) {
      limpiarDisplay();
      int a = solicitarNumero("Digita el primer número:");
      int b = solicitarNumero("Digita el segundo número:");
      int r = a * b;

      Serial.println("El resultado es:");
      Serial.println(r);
      mostrarResultado(r);
      Serial.println("Multiplicación realizada");
    }

    // Operación de División
    bool mnemonic3 = strcmp(data, "DIV");
    if (!mnemonic3) {
      limpiarDisplay();
      int a = solicitarNumero("Digita el primer número:");
      int b = solicitarNumero("Digita el segundo número:");

      if (a == 0 && b == 0) {
        Serial.println("Error: División de cero entre cero es indefinido.");
        mostrarResultado(-2);  
        return;                // Termina la función para evitar procesar más
      }
      if (a != 0 && b == 0) {
        Serial.println("Error: División entre cero es infinito.");
        INFINITO();  
      } else {
        int r = a / b;
        Serial.println("El resultado es:");
        Serial.println(r);
        mostrarResultado(r);
        Serial.println("División realizada");
      }
    }

    bool mnemonicAND = strcmp(data, "AND");
    if (!mnemonicAND) {
      limpiarDisplay();
      int a = solicitarBinario("Ingrese el primer valor binario (0 o 1): ");
      int b = solicitarBinario("Ingrese el segundo valor binario (0 o 1): ");
      int r = a & b;
      mostrarResultado(r);
      Serial.println("Operación AND realizada");
    }

    bool mnemonicOR = strcmp(data, "OR");
    if (!mnemonicOR) {
      limpiarDisplay();
      int a = solicitarBinario("Ingrese el primer valor binario (0 o 1): ");
      int b = solicitarBinario("Ingrese el segundo valor binario (0 o 1): ");
      int r = a | b;
      mostrarResultado(r);
      Serial.println("Operación OR realizada");
    }

    bool mnemonicNOT = strcmp(data, "NOT");
    if (!mnemonicNOT) {
      limpiarDisplay();
      int a = solicitarBinario("Ingrese el valor binario (0 o 1) para NOT: ");
      int r = !a;
      mostrarResultado(r);
      Serial.println("Operación NOT realizada");
    }

    bool mnemonicXOR = strcmp(data, "XOR");
    if (!mnemonicXOR) {
      limpiarDisplay();
      int a = solicitarBinario("Ingrese el primer valor binario (0 o 1): ");
      int b = solicitarBinario("Ingrese el segundo valor binario (0 o 1): ");
      int r = a ^ b;
      mostrarResultado(r);
      Serial.println("Operación XOR realizada");
    }

    bool mnemonicNOR = strcmp(data, "NOR");
    if (!mnemonicNOR) {
      limpiarDisplay();
      int a = solicitarBinario("Ingrese el primer valor binario (0 o 1): ");
      int b = solicitarBinario("Ingrese el segundo valor binario (0 o 1): ");
      int r = !a & !b;
      mostrarResultado(r);
      Serial.println("Operación NOR realizada");
    }

    bool mnemonicXNOR = strcmp(data, "XNOR");
    if (!mnemonicXNOR) {
      limpiarDisplay();
      int a = solicitarBinario("Ingrese el primer valor binario (0 o 1): ");
      int b = solicitarBinario("Ingrese el segundo valor binario (0 o 1): ");
      int r = !(a ^ b);
      mostrarResultado(r);
      Serial.println("Operación XNOR realizada");
    }

    bool mnemonicNAND = strcmp(data, "NAND");
    if (!mnemonicNAND) {
      limpiarDisplay();
      int a = solicitarBinario("Ingrese el primer valor binario (0 o 1): ");
      int b = solicitarBinario("Ingrese el segundo valor binario (0 o 1): ");
      int r = !(a & b);
      mostrarResultado(r);
      Serial.println("Operación NAND realizada");
    }
  }
}

// Función para limpiar el display
void limpiarDisplay() {
  for (int Pin = 13; Pin >= 6; Pin--) {
    digitalWrite(Pin, LOW);
  }
}

int solicitarNumero(String mensaje) {
  String input = "";
  Serial.println(mensaje);

  while (true) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == '\r') {  // Detecta Enter
        break;
      } else {
        input += c;  // Agrega el carácter a la cadena
      }
    }
  }
  Serial.println(input);
  return input.toInt();  // Convierte la cadena a un número
}

int solicitarBinario(const char* mensaje) {
  int valor = -1;
  while (valor != 0 && valor != 1) {
    Serial.println(mensaje);
    String input = "";
    while (true) {
      if (Serial.available()) {
        char c = Serial.read();
        if (c == '\r') {
          break;
        } else {
          input += c;
        }
      }
    }
    valor = input.toInt();
    if (valor != 0 && valor != 1) {
      Serial.println("Valor no válido. Por favor, ingrese 0 o 1.");
    } else {
      Serial.println(valor);
    }
  }
  return valor;
}

void mostrarResultado(int resultado) {
  limpiarDisplay();  // Asegura que el display esté limpio
  switch (resultado) {
    case 0:
      CERO();
      break;
    case 1:
      UNO();
      break;
    case 2:
      DOS();
      break;
    case -1:
      SIGNO();  // 1 con signo negativo
      break;
    case -2:  // Caso especial para divisiones indefinidas
      Serial.println("El resultado de la Division es indefinido.");
      INDEFINIDO();
      break;
    default:
      Serial.println("El resultado está fuera del rango del display.");
      FueraRango();
      break;
  }
}

// Funciones de segmentos para mostrar números
void CERO() {
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
}

void UNO() {
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
}

void DOS() {
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(13, HIGH);
}

void SIGNO() {
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(13, HIGH);
}

void INDEFINIDO() {  // Forma de U para indicar error
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
}

void INFINITO() {  //Forma de 8
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
}

void FueraRango() {
  digitalWrite(13, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(6, HIGH);
}