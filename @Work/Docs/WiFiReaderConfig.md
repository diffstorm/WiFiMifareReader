Wifi Reader config
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

## Geçiş tipi?
- Giriş/Çıkış

## Internet wifi
- ssid, password - listeden sec?
- anten gucu ayari

## AP wifi
- Ssid, password

## Wifi calisma modu
- AP acik/kapali
- mDNS name (http://name.local)

## Kapida role var mi?
- ismi? - listeden sec
5 roleye kadar eklenebilsin
- [x] rölelerle ağ üzerinden haberleş
- [ ] rölelerle direkt haberleş (düşük güç modunda önerilir)

## Giris restrictions?
- Aktif saat araligi  (9-18)
- Aktif haftanin gunu
Bu saatlerde yonetici karti haric kapiyi acmaz!
- [ ] Ziyaretçi kartı geçiş yapabilsin mi?
- [x] Bekçi kartı geçiş yapabilsin mi?

## Loglama yapilsin mi?
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
- [ ] IR aktif

## Yazilim guncellemeleri?
- [x] Otomatik al
- Kontrol sıklığı - hergun/hafta/ay
