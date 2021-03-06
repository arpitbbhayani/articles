Would you shave your head and get it tattooed? Probably no, but a slave in ancient Greece was made to do so in the 440 BCE by a ruler named [Histiaeus](https://en.wikipedia.org/wiki/Histiaeus). The text that was tattooed was a secret message that Histiaeus wanted to send to his son-in-law Aristagoras in Miletus. After his hair grew back the slave left for Miletus and upon his arrival, his head was shaved again and the message was revealed which told Aristagoras to revolt against the Persians and start the [Ionian revolt](https://en.wikipedia.org/wiki/Ionian_Revolt).

This art of concealing message is called Steganography. The word is derived from the Greek word “στεγαυω” which means "secret or covered writing". In modern times, steganography can be looked into as the study of the art and science of communicating in a way that hides the presence of the communication.

Steganography continued over time to develop into new levels. Invisible inks, microdots, writing behind postal stamps are all examples of steganography in its physical form. Most of these early developments happened during World War I and II where everyone was trying to outsmart each other. The left half of the image below is a bunch of microdots, sent by German spies and intercepted by Allied intelligence, and the right half is the camera that was used to print such microdots.

![Microdots and Microdot Camera](https://user-images.githubusercontent.com/4745789/72497176-da0ccd80-3851-11ea-96b0-759d7e62f451.png)

### Steganography and Cryptography

Since the rise of the Internet, making communication more secure has been a priority. This lead to the development of the field of Cryptography that deals with hiding the meaning of a message. The techniques of cryptography try to ensure that it becomes extremely difficult to extract the true meaning of the message when it goes into the wrong hands.

Sometimes, it becomes necessary to not only hide the meaning of the message but also hide its existence, and the field that deals with this is called Steganography. Both cryptography and steganography, protect the information in their own way but neither alone is perfect and can be compromised. Hence a hybrid approach where we encrypt the message and then hide its presence amplifies the security.

Today steganography is mostly used on computers with digital data, like Image, Audio, Video, Network packets, etc, acting as the carriers. There are a bunch of techniques for each of them but this article aims to provide an exhaustive overview of Image Steganography.

# Image Steganography

Images are an excellent medium for concealing information because they provide a high degree of redundancy - which means that there are lots of bits that are there to provide accuracy far greater than necessary for the object's use (or display). Steganography techniques exploit these redundant bits to hide the information/payload by altering them in such a way that alterations cannot be detected easily by humans or computers.

## Color depth and definition

An image is a collection of numbers that defines color intensities in different areas of the image. It is arranged in a gird, which is the resolution of the image, and each point on the grid is called a pixel. Each pixel is defined by a fixed number of bits and this is its color scheme. The smallest color depth is 8 bit (in monochrome and greyscale images) and it displays 256 different colors or shades of grey as shown below.

![8-bit grayscale monochrome image](https://user-images.githubusercontent.com/4745789/72497072-8e5a2400-3851-11ea-9b28-8705bbfea070.png)

Digital color images are typically stored in 24-bit pixel depth and uses the RGB color model. All color variations for the pixels of a 24-bit image are derived from three primary colors: red, green and blue, and each primary color is represented by 8 bits. Thus each pixel takes one from a palette of 16-million colors.

![24-bit color palette](https://user-images.githubusercontent.com/4745789/72497287-23f5b380-3852-11ea-96e8-e5c8ffca0c9f.png)

## Compression

When working with high-resolution images with greater color depth, the size of the raw file can become big and it becomes impossible to transmit it over a standard internet connection. To remedy this, compressed image formats were developed which, as you would have guessed, compresses the pixel information and keeps file sizes fairly small, making it efficient for transmission.

Compression techniques can be broadly classified into the following two classes

### Lossy Compression
Lossy compression removes redundancies that are too small for the human eye to differentiate which makes the compressed files a close approximate, but not an exact duplicate of the original one. A famous file format that does lossy compression is [JPEG](https://en.wikipedia.org/wiki/JPEG).

### Lossless Compression
Lossless compression never removes any information from the original image, but instead represents data in mathematical formulas maintaining the integrity of the original image and when uncompressed, the file is a bit-by-bit copy of the original. Formats that do lossless compression are [PNG](https://en.wikipedia.org/wiki/Portable_Network_Graphics), [GIF](https://en.wikipedia.org/wiki/GIF), and [BMP](https://en.wikipedia.org/wiki/BMP_file_format).

Steganographic techniques take into account file formats, compression methods, and picture semantics and exploit them to find redundancies and use them to conceal secret information and can be broadly classified into two: spatial domain and frequency domain techniques, and we take a deeper look into both.

# Spatial Domain Techniques
Spatial domain techniques embed the secret message/payload in the intensity of the pixels directly; which means they update the pixel data by either inserting or substituting bits. Lossless images are best suited for these techniques as compression would not alter the embedded data. These techniques have to be aware of the image format to make concealing information fool-proof.

## LSB Substitution
This technique converts the secret message/payload into a bitstream and substitutes them into a least significant bit (the 8th bit) of some or all bytes inside an image. The alterations happen on the least significant bit which changes the intensity by +-1 which is extremely difficult for the human eye to detect.

![LSB substitution](https://user-images.githubusercontent.com/4745789/72587393-1eb06b80-391b-11ea-89ce-eb72be220a89.png)

When using a 24-bit image, a bit of each of the red, green and blue color components is substituted. Since there are 256 possible intensities of each primary color, changing the LSB of pixel results in small changes in the intensity of the colors.

![24-bit image LSB substitution](https://user-images.githubusercontent.com/4745789/72589054-2de5e800-3920-11ea-9c0a-c9f878fcd525.png)

See if you can spot what has changed in the images below. The image on the right has about 1KB long text message embedded through LSB substitution but looks the same as the original image.

![LSB substitution cat image difference](https://user-images.githubusercontent.com/4745789/72535218-31d12600-389e-11ea-9463-011fa42e430c.png)

In a 24 bit image we can store 3 bits in each pixel hence an 800 × 600 pixel image, can thus store a total amount of 1,440,000 bits or 180,000 bytes ~ 175KB of embedded data.

## Extending LSB to k-LSB
To hold more data into the image we can substitute not `1` but `k` least significant bits. But when we do so the image starts to distort which is never a good sign but a well-chosen image could do the trick and you wouldn't notice any difference.

## Randomized LSB
A regular LSB substitution technique starts substituting from pixel `0` and goes till `n` making this method highly predictable. To make things slightly challenging sender and receiver could share a secret key through which they agree on the certain pixels that will be altered making the technique more robust.

## Adaptive LSB
Adaptive LSB uses k-bit LSB and varies `k` as per the sensitivity of the image region over which it is applied. The method analyzes the edges, brightness, and texture of the image and calculates the value of `k` for that region and then does regular k-LSB substitution on it. It keeps the value of `k` high at a not-so-sensitive image region and low at the sensitive region. These alterations ensure that the overall quality of the image is balanced and distortions harder to detect.

**Pixel-value differencing (PVD)** scheme is a concrete implementation of adaptive LSB and it uses the difference of values between two consecutive pixels in a block to determine the number of secret bits to be embedded.

## LSB and Palette Based Images
The persistence of Palette Based Images is very interesting. There is a color lookup table which holds all the colors that are used in the image. Each pixel is represented as a single byte and the pixel data is an index to the color palette. [GIF](https://en.wikipedia.org/wiki/GIF) images work on this principle; it cannot have a bit depth greater than 8, thus the maximum number of colors that a GIF can store is 256. Now if we perform LSB substitution to pixel data then it changes the index in the lookup table (palette) and the new value (after substitution), that points to the index on the lookup table (palette), could point to a different color and the change will be evident. We could still do steganography on palette-based images using following workarounds

![palette-based image](https://user-images.githubusercontent.com/4745789/72600791-4ebb3700-393a-11ea-8e3e-2ddf389e85d1.png)

### Sorting the palette
The LSB substitution alters the value by +-1 and hence it will always point to a neighboring entry in the table. Hence we sort the palette by color then this will make adjacent lookup table entries similar to each other and minimize the distortion.

### Add new colors to the palette
If the original image has fewer colors then we could add similar colors in color palette/lookup table and then perform regular LSB substitution. Again the +-1 alteration will make that pixel point to some similar color in the lookup table.

## Other techniques
Apart from the above-mentioned LSB substitution technique, there are techniques that exploit some aspect of the image and embeds data. I would highly recommend you at least give a skim to each of the below:

 - [Edges based data embedding method (EBE)](https://link.springer.com/article/10.1186/1687-417X-2014-8)
 - [Random pixel embedding method (RPE)](https://ieeexplore.ieee.org/abstract/document/8276335)
 - [Mapping pixel to hidden data method](https://www.researchgate.net/publication/26623039_Image_Steganography_by_Mapping_Pixels_to_Letters)
 - [Labeling or connectivity method](https://www.researchgate.net/publication/239551978_Labeling_Method_in_Steganography)

# Frequency Domain Techniques
Spatial domain techniques directly start putting in data from payload into an image but Frequency-domain techniques will first transform the image and then embed the data. The transformation step ensures that the message is hidden in less sensitive areas of the image, making the hiding more robust and makes the entire process independent of the image format. The areas in which the information is hidden are usually less exposed to compression, cropping, and image processing.

These techniques are relatively complex to comprehend and require a bit of advanced mathematics to understand thoroughly. Images with lossy compression are ideal candidates and hence we dive a little deep into how JPEG steganography works.

## JPEG steganography
To understand how steganography works for JPEG files, we will look into: how the raw data is compressed by JPEG and then we see how we could hide data in it.

### JPEG Compression
According to research, the human eye is more sensitive to changes in the brightness (luminance) of a pixel than to changes in its color. We interpret brightness and color by contrast with adjacent regions. The compression phase takes advantage of this insight and transforms the image from RGB color to [YCbCr](https://en.wikipedia.org/wiki/YCbCr) representation - separating brightness from color. In YCbCr representation, the Y component corresponds to luminance (brightness - black-white) and Cb (yellow-blue) and Cr (green-red) components for chrominance (color). Now we discard some of the color data by downsampling it to half in both horizontal and vertical directions thus directly reducing the size of the file by a factor of 2.

![YCbCr transformation](https://user-images.githubusercontent.com/4745789/72549559-f1ca6d00-38b6-11ea-9760-bd1f35dbf455.png)

Now the image, in YCbCr representation, is processed in blocks of 8 x 8 and we perform [Discrete Cosine Transform (DCT)](https://en.wikipedia.org/wiki/Discrete_cosine_transform) on each, then quantized (rounding) 64 values into 1 by taking the average. The quantization step is the one that removes redundant information from the image. To dive more into DCT on JPEG, I would recommend you watch this [Computerphile video](https://www.youtube.com/watch?v=Q2aEzeMDHMA).

This is the first stage of JPEG compression which is lossy. Now this image data is then losslessly compressed using the standard [Huffman encoding](https://en.wikipedia.org/wiki/Huffman_coding).

### JPEG Steganography
Since JPEG images are already lossily compressed (redundant bits are already thrown out) it was thought that steganography would not be possible on it. So if we would try to hide or embed any message in it, it might get either lost, destroyed or altered during compression, adding some noticeable changes to the image. The complete JPEG encoding process is as shown in the diagram below

![JPEG Process](https://user-images.githubusercontent.com/4745789/72615006-a87f2980-3959-11ea-872f-733c9523a411.png)

The entire process could be split into two stages, the first is where redundancy is removed and the second is where the data is encoded using Huffman encoding. During the DCT transformation phase, rounding errors occur in the coefficient data that are not noticeable and this makes the algorithm lossy. Once this stage is over we have a chance to perform usual LSB substitution and embed the message. Since stage 2 of JPEG compression is lossless, due to Huffman encoding, we are sure that none of our substituted data will be lost. Thus we sandwich the steganography between the lossy and lossless stages of JPEG compression.

## Other techniques
Apart from the above-mentioned DCT technique, there are techniques that use a different form of transform signal and embeds secret data. To name a few

 - [Discrete Fourier transformation technique (DFT)](https://link.springer.com/chapter/10.1007/978-3-642-20998-7_39)
 - [Discrete Wavelet transformation technique (DWT)](https://www.insight-centre.org/sites/default/files/publications/17.197_a_steganography_technique_for_images_based_on_wavelet_transform.pdf)
 - [Lossless or reversible method (DCT)](https://www.researchgate.net/publication/330565811_Hiding_data_in_images_using_DCT_steganography_techniques_with_compression_algorithms)
 - [Embedding in coefficient bits](http://www.ijcee.org/papers/533-P0025.pdf)

# Conclusion
This is the first article in the series of Steganography that detailed out Image Steganography. I hope you reaped some benefits out of it. The future articles on Steganography will talk about how it is done on carriers like Audio, Network, [DNA](https://www.sciencedirect.com/science/article/pii/S1877050917319804) and [Quantum states](https://arxiv.org/abs/1006.1934) and will also dive into one of the most interesting applications of Steganography - a [Steganographic File System](https://en.wikipedia.org/wiki/Steganographic_file_system). So stay tuned and watch this space for more.
