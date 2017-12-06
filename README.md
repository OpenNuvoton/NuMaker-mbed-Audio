# NuMaker-mbed-Audio
This library contains Mbed implementation of NuMaker Audio I2S and Codec.

### Example: Play PCM data from SD card

1. Declare NuSDBlockDevice and FATFileSystem.
    
    ```
    NuSDBlockDevice bd   // device SD driver
    FATFileSystem fs     // Mbed FAT file system
    ```
    
1. Declare audio.
    
    ```
    NAU8822L audio  // NAU8822L object, I2C pinout/address and I2S pinout
    or
    NAU88L25 audio  // NAU88L25 object, I2C pinout/address and I2S pinout
    ```
    
1. Attach callback function for playing.
    
    ```
    audio.attach(&play);
    ```
    
1. Start audio.
    
    ```
    audio.start();
    ```
    
1. Stop playing.
    
    ```
    audio.stop();
    ```
    
1. Write PCM data to audio.
    
    ```
    audio.write
    ```
    
### Example: Record PCM data to SD card

1. Attach callback function for recording.
    
    ```
    audio.attach(&record);
    ```
    
1. Record audio.
    
    ```
    audio.record();
    ```
    
1. Stop recording.
    
    ```
    audio.stop();
    ```
    
1. Read PCM data from audio.
    
    ```
    audio.read();
    ```
    
### Notes:

1. Smoothly playing or recording depends on the performance of SD card.

1. Use FFmpeg to convert a PCM file.
    
    ```
    ffmpeg.exe -hide_banner -i audio_file -map_metadata -1 -flags +bitexact -vn -sn -c:a pcm_s16le -ac 1 -ar 8000 -f s16le test.pcm
    ```
    