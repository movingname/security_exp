openssl enc -aes-128-ecb -in pic_original.bmp -out ecb_bmp \
			-K 00112233445566778889aabbccddeeff \
			-iv 0102030405060708
