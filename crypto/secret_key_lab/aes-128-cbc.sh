openssl enc -aes-128-cbc -in plain.txt -out cipher.bin \
			-K 00112233445566778889aabbccddeeff \
			-iv 0102030405060708
