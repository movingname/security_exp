openssl enc -aes-128-cbc -in pic_original.bmp -out cbc_bmp \
			-K 00112233445566778889aabbccddeeff \
			-iv 0102030405060708
