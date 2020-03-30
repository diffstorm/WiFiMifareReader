WiFi Relay Config 
===========================================

## Cihaza ait sabit bilgiler görüntülenir
- Unique Device ID
- Versiyon

## Kullanici bilgileri
- Firma ismi
- Departman ismi
- Cihaz ismi
- Cihaz aciklama
- Sistem Şifresi (tum cihazlarda aynı olmalı)
- Login usr:pwd [sor/sorma]

## Internet wifi
- ssid, password - listeden sec?
- anten gucu ayari

## AP wifi
- Ssid, password

## Wifi calisma modu
- AP acik/kapali
- mDNS name (http://name.local)

## WiFi Reader ile haberleşme yöntemi
- [x] wifi readerlarla ağ üzerinden haberleş
- [ ] wifi readerlarla direkt haberleş (reader düşük güç modunda önerilir)

## RF Reader dan komut dinle
- [ ] Açık/kapalı

## Loglama yapilsin mi?
Loglama sadece kapı açılması ve tarihi şeklinde yapılır.
- İletme zamanı :
  - [x] Belirli saatlerde ilet
    - Loglama saatleri (5 adet)
  - [x] Logu aninda ilet
  - [x] Hafiza dolunca ilet
- Loglama metodu :
  - mail
  - rest api (GET)
  - udp - address port
  - kendi ucretli platformumuz - token

## Yazilim guncellemeleri?
- [x] Otomatik al
- Kontrol sıklığı - hergun/hafta/ay
