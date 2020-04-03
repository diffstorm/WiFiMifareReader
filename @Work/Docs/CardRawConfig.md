CardRawConfig
===========================================

- Checksum (CRC16 of Data[Length]) 
- Length (Length of data)
- Random (2 bytes long random number)
- BCC (Checksum + Length + Random)
- Data[Length] (16 bytes padding - encrypted with device password using TDES)
