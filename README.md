# NuMaker-mbed-Audio
This library contains mbed implementation of NuMaker Audio I2S and Codec.

### Example: PCM file playback from SD card

1. Declare NuSDFileSystem.

    ```
    NuSDFileSystem Nu_SD   // the pinout on the mbed Cool Components workshop board
    ```
1. Declare audio.

    ```
    NAU8822L audio  // NAU8822L object, I2C pinout, address, I2S pinout
    ```
1. Attach callback function.

    ```
    audio.attach(&play);
    ```
    
1. Start audio.

    ```
    audio.start();
    ```
    
1. Write PCM data to audio.

    ```
    audio.write
    ```
