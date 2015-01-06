test = '<b">">"foo"</b>'
tagmode = False
escapemode = False
escapes = ['\\', '"']
output = ""

for letter in test:
	if letter in escapes and tagmode:
		escapemode = not escapemode
	if not escapemode:
		if letter in ['<']:
			tagmode = True
		elif letter in ['>']:
			tagmode = False
		elif not tagmode:
			output += letter

print output