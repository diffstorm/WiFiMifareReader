Wifi Reader config
===========================================

## Cihaza ait sabit bilgiler görüntülenir
- Unique Device ID
- FW Version
- Device Model
- Cihaz MAC
- Cihaz IP
- Hafıza doluluk
- Kayıtlı kart sayısı
- Kayıtlı log sayısı
- Tarih-Saat

## Kullanici bilgileri
- Firma ismi
- Departman ismi
- Cihaz ismi
- Cihaz aciklama
- Sistem Şifresi (tum cihazlarda aynı olmalı)
- Web Login password
- mDNS name (http://name.local)

## Geçiş tipi?
- Giriş/Çıkış

## wifi
- STA ssid, password - listeden sec?
- STA acik/kapali
- APP ssid, password
- AP acik/kapali

## Kapida role var mi?
- ismi? - listeden sec
_5 roleye kadar eklenebilsin_
- [x] rölelerle ağ üzerinden haberleş
- [ ] rölelerle direkt haberleş (düşük güç modunda önerilir)

## Giris restrictions?
- Aktif saat araligi  (9-18)
- Aktif haftanin gunu
_Bu saatlerde yonetici karti haric kapiyi acmaz!_
- [ ] Ziyaretçi kartı geçiş yapabilsin mi?
- [x] Bekçi kartı geçiş yapabilsin mi?

## Loglama yapilsin mi?
- İletme zamanı :
  - [x] Belirli saatlerde ilet
    - Loglama saatleri (5 adet)
  - [x] Logu aninda ilet
  - _Hafiza dolunca otomatik iletir!_
- Loglama metodu :
  - Mail
  - REST api (GET)
  - UDP - address port
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
- anten gucu ayari
- kalibrasyon ayarı (init hızı)

## Yazilim guncellemeleri?
- [x] Otomatik al
- Kontrol sıklığı - hergun/hafta/ay
