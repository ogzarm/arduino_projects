#include <dht11.h> // dht11 kütüphanesini ekliyoruz.
#include <SD.h>
File myFile;
#define DHT11PIN 2 // DHT11PIN olarak Dijital 2"yi belirliyoruz.

dht11 DHT11;

void setup()
{
  Serial.begin(9600); // Seri iletişimi başlatıyoruz.
  Serial.println("DHT11 Test Programi");
 
while (!Serial) ;       //seri porta baglanti yapilana kadar bekle

if (!SD.begin(4)) {
Serial.println("SD/MMC karta baglanti basarisiz");
return;

}
//dosya yok ise olusturuluyor
myFile = SD.open("test.txt", FILE_WRITE);

if (myFile) {
Serial.print("test.txt yaziliyor…");

//her seferinde var olan dosyanin uzerine yaziyor
myFile.println("deneme yazisi 1234");

myFile.close();
Serial.println("tamamlandi.");
} else {

Serial.println("test.txt acilamadi");
}

myFile = SD.open("test.txt");
if (myFile) {
Serial.println("test.txt");
while (myFile.available())

{
Serial.write(myFile.read());

}

myFile.close();
} else {

Serial.println("test.txt acilamadi");
}
}
//setup bitti

void loop()
{
  // Bir satır boşluk bırakıyoruz serial monitörde.
  myFile.println();
  // Sensörün okunup okunmadığını konrol ediyoruz. 
  // chk 0 ise sorunsuz okunuyor demektir. Sorun yaşarsanız
  // chk değerini serial monitörde yazdırıp kontrol edebilirsiniz.
  int chk = DHT11.read(DHT11PIN);

  // Sensörden gelen verileri serial monitörde yazdırıyoruz.
  myFile.print("Nem (%): ");
  myFile.println((float)DHT11.humidity, 2);

  myFile.print("Sicaklik (Celcius): ");
  myFile.println((float)DHT11.temperature, 2);

  myFile.print("Sicaklik (Fahrenheit): ");
  myFile.println(DHT11.fahrenheit(), 2);

  myFile.print("Sicaklik (Kelvin): ");
  myFile.println(DHT11.kelvin(), 2);

  // Çiğ Oluşma Noktası, Dew Point
  myFile.print("Cig Olusma Noktasi: ");
  myFile.println(DHT11.dewPoint(), 2);

  // 2 saniye bekliyoruz. 2 saniyede bir veriler ekrana yazdırılacak.
  delay(2000);

}
