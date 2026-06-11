import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;

Serial port;

String angle = "";
String distance = "";
String data = "";
String noObject = "";

float pixsDistance;
int iAngle = 0;
int iDistance = 0;
int index1;

PFont orcFont;

void setup() {

  size(800, 600);
  smooth();

  printArray(Serial.list());

  // Altere caso sua porta seja diferente
  port = new Serial(this, "/dev/ttyUSB0", 9600);
  port.bufferUntil('\n');

  orcFont = createFont("Monospaced", 24);
  textFont(orcFont);

  background(0);
}

void draw() {

  fill(0, 25);
  noStroke();
  rect(0, 0, width, height);

  fill(98, 245, 31);

  drawRadar();
  drawLine();
  drawObject();
  drawText();
}

void serialEvent(Serial p) {

  String s = p.readStringUntil('\n');

  if (s == null) {
    return;
  }

  s = trim(s);

  index1 = s.indexOf(',');

  if (index1 < 0) {
    return;
  }

  try {

    angle = s.substring(0, index1);
    distance = s.substring(index1 + 1);

    iAngle = Integer.parseInt(angle);
    iDistance = Integer.parseInt(distance);

  } catch (Exception e) {
    println("Erro: " + s);
  }
}

void drawRadar() {

  pushMatrix();

  translate(width / 2, height - 50);

  noFill();
  stroke(98, 245, 31);
  strokeWeight(2);

  arc(0, 0, 600, 600, PI, TWO_PI);
  arc(0, 0, 450, 450, PI, TWO_PI);
  arc(0, 0, 300, 300, PI, TWO_PI);
  arc(0, 0, 150, 150, PI, TWO_PI);

  line(-300, 0, 300, 0);

  for (int a = 30; a <= 150; a += 30) {
    line(
      0,
      0,
      300 * cos(radians(a)),
      -300 * sin(radians(a))
    );
  }

  popMatrix();
}

void drawLine() {

  pushMatrix();

  translate(width / 2, height - 50);

  stroke(30, 250, 60);
  strokeWeight(3);

  line(
    0,
    0,
    300 * cos(radians(iAngle)),
    -300 * sin(radians(iAngle))
  );

  popMatrix();
}

void drawObject() {

  pushMatrix();

  translate(width / 2, height - 50);

  stroke(255, 0, 0);
  strokeWeight(8);

  // Escala: 1 cm = 7 pixels
  pixsDistance = iDistance * 7;

  if (pixsDistance > 300) {
    pixsDistance = 300;
  }

  if (iDistance < 40) {

    line(
      pixsDistance * cos(radians(iAngle)),
      -pixsDistance * sin(radians(iAngle)),
      0,
      0
    );
  }

  popMatrix();
}

void drawText() {

  fill(98, 245, 31);

  textSize(20);

  if (iDistance >= 40) {
    noObject = "Fora de alcance";
  } else {
    noObject = "Objeto detectado";
  }

  text("Angulo: " + iAngle + "°", 20, 30);
  text("Distancia: " + iDistance + " cm", 20, 60);
  text(noObject, 20, 90);

  text("10 cm", width / 2 + 75, height - 60);
  text("20 cm", width / 2 + 150, height - 60);
  text("30 cm", width / 2 + 225, height - 60);
  text("40 cm", width / 2 + 300, height - 60);
}
