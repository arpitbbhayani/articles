Would you shave your head and get it tattooed? Probably no, but a slave in ancient Greece was made to do so in the 440 BCE by a ruler named [Histiaeus](https://en.wikipedia.org/wiki/Histiaeus). The text that was tattooed was a secret message that Histiaeus wanted to send to his son-in-law Aristagoras in Miletus. After letting his hair grow back the slave left for Miletus and upon his arrival, the head was shaved again and the message was revealed which told Aristagoras to revolt against the Persians and start the [Ionian revolt](https://en.wikipedia.org/wiki/Ionian_Revolt).

This art of concealing message is called Steganography. The word is derived from the Greek word “στεγαυω” which means "secret writing". In modern times, steganography can be looked into as the study of the art and science of communicating in a way that hides the presence of the communication.

Steganography continued over time to develop into new levels. Invisible inks, microdots, writing behind postal stamps are all examples of Steganography in its physical form. Most of these early developments happened during World War I and II where everyone was trying to outsmart each other.

Post the digital revolution, we started manipulating media like Images, Audio, Video, Network Packets, DNA, Quantum, etc to conceal information. There are a bunch of techniques in each of the mentioned segment but in this article, we will focus on Image Steganography.

# Image Steganography

An image is composed of pixels and each pixel has 3 component for 3 primary colors Red, Blue and Green. Depending on the intensity of each color their superposition determines the final color of the pixel. For example: to get nice pink shade we need to mix r, g and b in proportion. Red plus blue gives yellow.

![rgb superposition](https://user-images.githubusercontent.com/4745789/72423143-c6a62780-37a9-11ea-9ea9-0c3af74f98d0.png)

We perceive image as a whole, we never do it pixel by pixel. Hence unless there is huge difference between pixel we cannot comprehend the difference.
Image steganography uses this to conceal information within an image. There are various method to do that. we will look at LSB substitution in depth and will walk you through the other methods as well. LSB is the easiest of all and is an excellent way to get started with Image steganography.

## LSB Substitution

An image is rendered using pixels and each pixel contains 3 primary color components - red, blue and green. A pixel is rendered as a combination of color intensity of these 3 components. Intensity of each primary color ranges from 0 to 255 (both inclusive); which means each will take up 8 bits thus each pixel takes up 3 x 8 = 24 bits of space.

GIF OF COLOR WHEEL SHOWCASING EACH COLOR GOES HERE.

When intensity of a primary color within a pixel is changed it results in a new color, but if this alteration is by a very small delta then our eye cannot tell the difference as the new color will be very very close to old color.

![Color +-5 for RGB](https://user-images.githubusercontent.com/4745789/72420704-37971080-37a5-11ea-9d28-54cce1efaae7.png)

Image steganography uses this to conceal information in image pixel by altering each pixel by a very very small delta.

The binary representation of this intensity 0 - 255 is an 8 bit sequence. If we alter the least significant bit all we are doing it +- 1 which means the resulting color will be very close to original.

Example

Instead of doing it for LSB. do it for 2-3 bits in one primary color.

Example of how color gets affected.

### How to do it

Take an image in which you want to conceal information. This cat image looks purrrfect for that

Get a text file with your secret in it

### Concealing the data

Code to get bit stream from it

Code to update image and save

IMAGE THAT SHOWS THE DIFFERENCE

### REtrieving the data

Read first 2 bits that suggest length

Itereate and compose bit stream

bits to text

### Finding limits

Find amount of data you could conceal in an image.

And distortion you get in image due to it.

What happens when you do it for 2 bits

What happens when you do it for 3 bits

## Randomized LSB Substitution

Upgrade over predictable LSB

[a](https://pdfs.semanticscholar.org/c3c9/9ceaffb05c380b9953933945a9cd6fc1f707.pdf)
[b](https://www.lirmm.fr/~wpuech/enseignement/master_informatique/Compression_Insertion/articles/10_article_examen_PUECH_compression.pdf)

## Other methods in image

[](https://pdfs.semanticscholar.org/bb26/1e7f02f8597b37a2f71e55c2e2c21aa7575f.pdf)
[](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.364.3275&rep=rep1&type=pdf)
[](http://bit.kuas.edu.tw/~jihmsp/2011/vol2/JIH-MSP-2011-03-005.pdf)

# Other steganography in Digital Space

### Audio

### Video

### DNA

### Quantum

# Conclusion

This is the first article in the series of Steganography that detailed out Image Steganography. I hope you reaped some benefits out of it. The future articles on Steganography will talk about how Steganography is done on carriers like Audio, Network, DNA and Quantum states and will also dive into one of the most interesting applications of Steganography - a Steganographic File System. So stay tuned and watch this space for more.
