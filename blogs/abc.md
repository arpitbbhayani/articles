Would you shave your head and get it tattooed? Probably no, but a slave in ancient Greece was made to do so in the 440 BCE by a ruler named [Histiaeus](https://en.wikipedia.org/wiki/Histiaeus). The text that was tattooed was a secret message that Histiaeus wanted to send to his son-in-law Aristagoras in Miletus. The slave was made to go to Miletus only after his hair grew back. Upon his arrival, the head was shaved again and the message was revealed which told Aristagoras to revolt against the Persians and start the [Ionian revolt](https://en.wikipedia.org/wiki/Ionian_Revolt).

This art of concealing message is called Steganography. The word is derived from the Greek word “στεγαυω” which means "secret writing". In modern times, steganography can be looked into as the study of the art and science of communicating in a way that hides the presence of the communication.

Steganography continued over time to develop into new levels. Physical Steganography is where the information is hidden in some physical form ex: Invisible Ink, Microdot, Postal Stamps, etc. The early developments of this type happened during World War where everyone was trying to outsmart each other.

Post the digital revolution, we started manipulating media/carriers like Images, Audio, Video, Network Packets, DNA, Quantum, etc to conceal information since 1985. There are a bunch of techniques in each of the mentioned segment but in this article, we will focus on Image Steganography; other techniques will be covered in future articles.

# Image Steganography

A digital carrier is just a bunch of 1's and 0's arranged in some particular order, which when processed by some program makes some sense.

A character `B` has ASCII code of `66` which on disk is stored as `01000010` now if we change even one bit of this sequence, it will no longer represent `B` but some other character. This change will make our text erroneous and we will easily sense something is wrong.

But for an image the output

Changing a 1 to a 0 will make it a completely different thing. For example, the character `B` is `066` which on disk will be stored as `01000010`. Now if we change even 1 bit of this the sequence will now represent some other character. Let's say we change the least significant bit from `0` to `1` we get `01000011` which now represents character `C`.

An image, as we know has some resolution which defines the number of pixels


A typical resolution of an image 640 x 480px which means there are more than 307K pixels and each pixel constitutes 3 values one for each red, blue and green component and each component is 8 bit long.


When it comes to digital images, specifically in regards to steganography, there are three primary classes. Their file types are those with lossy-compression, those with lossless-compression, and raw file types. We will be working with lossless-compression file types. Lossless and lossy compressed file types are most common in the world today because of their compact size.

Of these, raw files are typically the easiest to work with. However they tend to be very large files, are not commonly used by most consumers, and often require special software used professional photographers or enthusiasts in order to view and edit. Some examples of raw image file formats are RAW and DNG.

Lossless-compression means that the files are stored in a compressed format, but that this compression does not result in the actual data being modified when the file is opened, transported, or decompressed. For lossless files steganography is often accomplished by manipulating the least-significant bits (LSB) of the carrier file. Some examples of lossless-compression image file formats are PNG, TIFF, an BMP.

Lossy-compression is the opposite of lossless-compression. When lossy compression is used there is no guarantee that the file will not be modified slightly when subjected to storage, transmission, or decompression. In nearly all cases this modification will be imperceptible to the end user, otherwise it wouldn’t be very popular. However, since LSB steganography will modify these “unimportant” bits that can be lost during compression doing steganography on files with lossy-compression is more complex. This means we can’t risk using lossy compression that may not preserve our modifications. Some examples of lossy-compression image file formats are JPEG and BPG.

## LSB Substitution

### Code

### Finding limits

## Randomized LSB Substitution

## Other methods in image

# Other steganography in Digital Space

### Audio Steganography

### Video

### DNA

### Quantum

# Conclusion

This is the first article in the series of Steganography that detailed out Image Steganography. I hope you reaped some benefits out of it. The future articles on Steganography will talk about how Steganography is done on carriers like Audio, Network, DNA and Quantum states and will also dive into one of the most interesting applications of Steganography - a Steganographic File System. So stay tuned and watch this space for more.
