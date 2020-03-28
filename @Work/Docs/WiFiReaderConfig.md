Wifi Reader config
===========================================

## Cihaza ait sabit bilgiler
- Unique Device ID goruntulenecek

## Kullanici bilgileri
- Firma ismi
- Departman ismi
- Cihaz ismi
- Cihaz aciklama
- Sistem Şifresi (auto uret)
- Login usr:pwd [sor/sorma]

## Geçiş tipi?
- Giriş/Çıkış

## Internet wifi
- 3 adet Ssid, password - listeden sec?
- anten gucu ayari

## AP wifi
- Ssid, password

## Wifi calisma modu
- AP acik/kapali
- mDNS name (http://name.local)

## Kapida role var mi?
- ismi? - listeden sec
5 roleye kadar eklenebilsin

## Giris restrictions?
- Aktif saat araligi  (9-18)
- Aktif haftanin gunu
Bu saatlerde yonetici karti haric kapiyi acmaz!

## Loglama yapilsin mi?
- İletme zamanı :
  - [x] Belirli saatlerde ilet
    - Loglama saatleri (5 adet)
  - [x] Logu aninda ilet
  - [x] Hafiza dolunca ilet
- Loglama metodu :
  - mail
  - rest api (GET)
  - database insert
    - ip/addr, user, pwd
  - tcp ip address port
  - kendi ucretli platformumuz
    - user, pwd yada token
- [x] Yetkisiz girisler loglansin mi?
- [ ] Yeni kart tanimlamalari loglansin mi?
- [ ] Kart silmeleri loglansin mi?
- [ ] Engellemeler loglansin mi?
- [ ] Config admin islemleri loglansin mi?

## Dusuk guc modu aktif mi?
- 5 farkli saat araligi icin kart tarama periyodu
  - [ ] Hepsi icin acik kapali checkbox
  - Saatler birbirlerini overlap yapamasin
- [x] Uyandirma butonu yada karti aktif

## Yazilim guncellemeleri?
- [x] Otomatik al
- Kontrol sıklığı - hergun/hafta/ay
