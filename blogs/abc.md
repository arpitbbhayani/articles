Would you shave your head and get it tattooed? Probably no, but a slave in ancient Greece was made to do so in the 440 BCE by a ruler named [Histiaeus](https://en.wikipedia.org/wiki/Histiaeus). The text that was tattooed was a secret message that Histiaeus wanted to send to his son-in-law Aristagoras in Miletus. After letting his hair grow back the slave left for Miletus and upon his arrival, the head was shaved again and the message was revealed which told Aristagoras to revolt against the Persians and start the [Ionian revolt](https://en.wikipedia.org/wiki/Ionian_Revolt).

This art of concealing message is called Steganography. The word is derived from the Greek word “στεγαυω” which means "secret writing". In modern times, steganography can be looked into as the study of the art and science of communicating in a way that hides the presence of the communication.

Steganography continued over time to develop into new levels. Invisible inks, microdots, writing behind postal stamps are all examples of steganography in its physical form. Most of these early developments happened during World War I and II where everyone was trying to outsmart each other.

![Microdots and Microdot Camera](https://user-images.githubusercontent.com/4745789/72497176-da0ccd80-3851-11ea-96b0-759d7e62f451.png)

The above image shows microdots and camera that generated them.

### Steganography and Cryptography

Since the rise of the Internet, the main concern has been the security of communication. The sole focus on making everything more secure by the day leads to the development of the field of Cryptography that deals with hiding the meaning of a message. The techniques of cryptography try to ensure that even when the message goes into the wrong hands. it is extremely difficult to extract the true meaning of the message.

Sometimes, it becomes necessary to not only hide the meaning of the message but also hide its existence, and the field that deals with this is called Steganography. Both the fields protect the information in their own way but neither alone is perfect and can be compromised. Hence a hybrid approach where we encrypt the message and then hide its presence amplifies the security.

Today steganography is mostly used on computers with digital data, like Image, Audio, Video, Network packets, etc, acting as the carriers/cover. There are a bunch of techniques for each of the mentioned carrier but this article only aims to provide an exhaustive overview of Image Steganography.

# Image Steganography

Images are an excellent medium for concealing information because they provide a high degree of redundancy - which means that there are lots of bits that provide accuracy far greater than necessary for object's use (display). Steganography techniques exploit these redundant bits to hide the information/payload by altering them in such a way that alterations cannot be detected easily.

## Color depth and definition

An image is a collection of numbers that defines color intensities in different areas of the image. It is arranged in a gird, which determines the resolution of the image, and each point on the grid is called a pixel. Each pixel is defined by a fixed number of bits and this is its color scheme. The smallest color depth is 8 bit, in monochrome and greyscale images, and it displays 256 different colors or shades of grey as shown below.

![8-bit grayscale monochrome image](https://user-images.githubusercontent.com/4745789/72497072-8e5a2400-3851-11ea-9b28-8705bbfea070.png)

Digital color images are typically stored in 24-bit pixel depth and use the RGB color model. All color variations for the pixels of a 24-bit image are derived from three primary colors: red, green and blue, and each primary color is represented by 8 bits. Thus each pixel can take of one color from a palette of 16-million colors.

![24-bit color palette](https://user-images.githubusercontent.com/4745789/72497287-23f5b380-3852-11ea-96e8-e5c8ffca0c9f.png)

## Compression

When working with larger images and greater color depth, the size of the raw file can become really really big and it becomes impossible to transmit it over a standard internet connection. To remedy this, compressed image formats were developed which, as you would have guessed, compresses the pixel information keeping file sizes fairly small making it efficient for transmission.

There are two types of compression techniques:

### Lossy Compression
Lossy compression removes redundancies that are too small for the human eye to differentiate and hence the compressed files are in close approximations of the original image, but not an exact duplicate. A famous file format that does lossy compression is [JPEG](https://en.wikipedia.org/wiki/JPEG).

### Lossless Compression
Lossless compression never removes any information from the original image, but instead represents data in mathematical formulas maintaining the integrity of the original image; which means when uncompressed the file is a bit-by-bit copy of the original. Formats that do lossless compression are [PNG](https://en.wikipedia.org/wiki/Portable_Network_Graphics), [GIF](https://en.wikipedia.org/wiki/GIF) and [BMP](https://en.wikipedia.org/wiki/BMP_file_format).

Steganographic techniques take into consideration the file format, compression method and picture semantic and look to exploit them by finding redundancies and using it to conceal extra information. Steganographic techniques can be broadly classified into two: spatial domain and frequency domain; we take a deeper look into both.

# Spatial Domain Techniques
Spatial domain techniques embed the secret message/payload in the intensity of the pixels directly; which means they update the pixel data by either inserting or substituting bits or manipulating noise in the image. Lossless images are best suited for these techniques as compression would not alter the embedded data. These techniques have to be aware of the image format to make concealing information fool-proof.

## LSB Substitution
This technique converts the secret message/payload into a bitstream and substitutes them into a least significant bit (the 8th bit) of some or all bytes inside an image. When using a 24-bit image, a bit of each of the red, green and blue color components is substituted. Since there are 256 possible intensities of each primary color, changing the LSB of pixel results in small changes in the intensity of the colors and this change cannot be perceived by the human eye. See the comparison below.

![lsb cat diff](https://user-images.githubusercontent.com/4745789/72535218-31d12600-389e-11ea-9463-011fa42e430c.png)

The image on the right has about 1KB long text message embedded through LSB substitution but can you spot any difference?

In a 24 bit image we can store 3 bits in each pixel hence an 800 × 600 pixel image, can thus store a total amount of 1,440,000 bits or 180,000 bytes ~ 175KB of embedded data.

### Extending LSB to k-LSB
To hold more data into the image we can substitute not `1` but `k` least significant bits. But we do so the image starts to distort which is never a good sign but a well-chosen image could do the trick and you wouldn't notice any difference.

## Randomized LSB
A regular LSB substitution technique starts substituting from pixel `0` and goes till `n`; this method is highly predictable. To make things slightly challenging sender and receiver could share a secret key through which they agree on the certain pixels that will be altered with LSB. This randomness makes LSB more secure and robust.

## Adaptive LSB
Adaptive LSB uses k-bit LSB and varies `k` as per the sensitivity of the image region over which it is applied. The method analyzes the edges, brightness, and texture of the image and calculates the value of `k` for that region and then does regular k-LSB on it. It keeps the value of `k` high at not-so-sensitive image region and low at the sensitive region. This balances the overall quality of the image and makes it even more difficult to see distortions.

Pixel-value differencing (PVD) scheme is a concrete implementation of adaptive LSB it uses the difference value between two consecutive pixels in a block to determine the number of secret bits to be embedded.

## LSB and Palette Based Images
The persistence of Palette Based Images is very interesting. There is a color lookup table which holds all the colors that are used in the image. Each pixel is represented as a single byte and the pixel data is an index to the color palette. This is usually the case with GIF images as it cannot have a bit depth greater than 8, thus the maximum number of colors that a GIF can store is 256.

The problem with the pallet approach is that if we perform LSB to pixel then it changes the index in the lookup table and the new value (after substitution) could point to a totally different color and the change will be evident. There are few solutions to tackle this:

### Sorting the pallette
If we sort the pallette then this will make adjacent lookup table entries similar thus we minimize the distortion.

### Add new colors to pallette
If the original image has fewer colors then we could add similar colors in color pallette/lookup table and then perform regular LSB substitution.

## Other techniques
Apart from the above-mentioned LSB substitution technique, there are several other techniques that exploit some aspect of the image and embeds data. I would highly recommend you at least give a skim to each of the following below:

 - Edges based data embedding method (EBE)
 - Random pixel embedding method (RPE)
 - Mapping pixel to hidden data method
 - Labeling or connectivity method

# Frequency Domain Techniques
Spatial domain techniques directly starts putting in data from payload into image but Frequency domain techniques will first transform the image and then embed the data. The transformation step ensures that the message are hidden in more significant/less sensitive areas of the image, making the hiding more robust and makes the entire process independent of the image format. The areas in which the information is hidden are usually less exposed to compression, cropping, and  image  processing.

These techniques relative complex to comprehend and required a bit of advanced mathematics to understand thoroughly. Images with lossy compression are ideal candidates and hence we dive a little deep into how JPEG steganography works.

## JPEG steganography
To understand how steganography works for JPEG files, we will look into: how the raw data is compressed by JPEG and then we see how we could hide data in it.

### JPEG Compression
According to research the human eye is more sensitive to changes in the brightness (luminance) of a pixel than to changes in its colour. We interpret brightness and color by contrast with adjacent regions. The compression phase takes advantage of this insight and transforms image from RGB color to [YCbCr](https://en.wikipedia.org/wiki/YCbCr) - separating brightness from color. In YUV representation the Y component corresponds to luminance (brightness - black-white) and Cb and Cr components for chrominance (color). Now we discard the color part from brightness by downsampling the color data to half in both horizontal and vertical directions thus directly halving the size of the file.

![YCbCr transformation](https://user-images.githubusercontent.com/4745789/72549559-f1ca6d00-38b6-11ea-9760-bd1f35dbf455.png)

Now the image in processed in blocks of 8 x 8 and we perform [Discrete Cosine Transform (DCT)](https://en.wikipedia.org/wiki/Discrete_cosine_transform) on each, then quantized (rounding) 64 values into 1 and eliminates small differences. To dive more into DCT on JPEG I would recommend you to watch this [Computerphile video](https://www.youtube.com/watch?v=Q2aEzeMDHMA).

This is the first stage of JPEG compression which is lossy. Now this image data is then losslessly compressed using standard [Huffman encoding](https://en.wikipedia.org/wiki/Huffman_coding).

### JPEG Steganography
Since JPEG images are already lossy compressed (redundant bits are already thrown out) it was thought that steganography would not be possible on it. So if would try to hide/embed any message in it, it might get lost/destroyed/altered during compression or worse it might make noticeable changes in the image. But there is one ray of hope ... rounding error during DCT.

During the DCT transformation phase of the compression algorithm, rounding errors occur in the coefficient data that are not noticeable. This rounding is what makes the algorithm lossy but could be used to hide information.

Thus it is important to recognize that the JPEG compression algorithm is actually divided into lossy and lossless stages. The DCT and the quantization phase form part of the lossy stage, while the Huffman encoding used to further compress the data is lossless.  Steganography can take place between these two stages

Using the same principles of LSB insertion the message can be embedded into the least significant bits of the coefficients before applying the Huffman encoding.  By embedding the information at this stage, in the transform domain, it is extremely difficult to detect, since it is not in the visual domain.

## Discrete Fourier transformation technique (DFT).
## Discrete cosine transformation technique (DCT)
## Discrete Wavelet transformation technique (DWT)
## Lossless or reversible method (DCT)
## Embedding in coefficient bits

# Spacial or Freq domain technique

## Patchwork
Patchwork is a statistical technique that uses redundant pattern encoding to embed a message in an image
The algorithm adds redundancy to the hidden information and then scatters it throughout the image.

A pseudorandom generator is used to select two areas of the image (or patches), patch A and patch B [22].  All the pixels in patch A is lightened while the pixels in patch B is darkened [22].  In other words the intensities of the pixels in the one patch are increased by a constant value, while the pixels of the other patch are decreased with the same constant value [6].  The contrast changes in this patch subset encodes one bit and the changes are typically small and imperceptible, while not changing the average luminosity

A disadvantage of the patchwork approach is that only one bit is embedded.  One can embed more bits by first dividing the image into sub-images and applying the embedding to each of them [23].  The advantage of using this technique is that the secret message is distributed over the entire image, so should one patch be destroyed, the others may still survive [17].  This however, depends on the message size, since the message can only be repeated throughout the image if it is small enough.  If the message is too big, it can only be embedded once

## Spread Spectrum
In spread spectrum techniques, hidden data is spread throughout the cover-image making it harder to detect

message is embedded in noise and then combined with the cover image to produce the stego image. Since the power of the embedded signal is much lower than the power of the cover image, the embedded image is not perceptible to the human eye or by computer analysis without access to the original image.

# Conclusion
This is the first article in the series of Steganography that detailed out Image Steganography. I hope you reaped some benefits out of it. The future articles on Steganography will talk about how Steganography is done on carriers like Audio, Network, DNA and Quantum states and will also dive into one of the most interesting applications of Steganography - a Steganographic File System. So stay tuned and watch this space for more.
