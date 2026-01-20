#!/usr/bin/env python3
import re
import unicodedata

# Removing accents like those found in Spanish names
#def remove_accents(text):
#  import unicodedata
#  try:
#    text = unicode(text, 'utf-8')
#  except NameError:
#    pass
#  text = unicodedata.normalize('NFD', text).encode('ascii', 'ignore').decode("utf-8")
#  return str(text)

def remove_accents(text):
  # Need to somehow check for Norwegian 'o' which is 0xF8 and replace with o which is 0x6F
  # If we don't replace manually, the character is removed.
  # This if for names like Hojgaard where the o looks like a null character
  new_text = ""
  for char in text:
    if ord(char) == 0xF8:
      print ('Norwegian character found in text: ' + text)
      new_text += 'o'
    else:
      new_text += char
      
  return unicodedata.normalize('NFKD', new_text).encode('ASCII', 'ignore').decode('utf-8', 'ignore')

def remove_end_of_name_carriage_return(text):
  cr_end_of_name = re.compile('([a-z])[\r\n]')
  III_regex = re.compile('(III)[\r\n]')
  matched = cr_end_of_name.search(text)
  matched_III = III_regex.search(text)
  temp_line = text
  
  if matched:
    match_pattern = matched.group(1)
    #Note group(1) should be the ([a-z]) match 
    #print('found match' + matched.group(1))
    sub_line = match_pattern + '\t'
    temp_line = cr_end_of_name.sub(sub_line, temp_line)
    #temp_line = re.sub(r'([a-z])\n', sub_line, temp_line)
  elif matched_III:
    match_pattern = matched_III.group(1)
    #Note group(1) should be the ([a-z]) match 
    #print('found match' + matched.group(1))
    sub_line = match_pattern + '\t'
    temp_line = III_regex.sub(sub_line, temp_line)
    
  print('remove_end_of_name_carriage_return(): ' + str(temp_line))  
  return str(temp_line)
  
def remove_amateur(text):
  amateur = re.compile(r' \(a\)')
  temp_line = amateur.sub('', text)
  return str(temp_line)
 
def remove_ties_carriage_return(text):
  cr_ties = re.compile('T[0-9]+[\r\n]')
  temp_line = cr_ties.sub('', text)
  return str(temp_line)
  
# Note - this did not work  
def remove_position(text):
  position_regex = re.compile('\b[0-9][\r\n]')
  temp_line = position_regex.sub('',text)
  return str(temp_line)
  
def remove_dash_carriage_return(text):
  regex_dash = re.compile(r'\-[\r\n]')
  temp_line = regex_dash.sub('', text)
  return str(temp_line)
  
def remove_commas(text):
  regex_comma = re.compile(',')
  temp_line = regex_comma.sub('',text)
  return str(temp_line)
  
def remove_countries(text):

  usa_regex = re.compile('United States[\r\n]')
  spain_regex = re.compile('Spain[\r\n]')
  england_regex = re.compile('England[\r\n]')
  australia_regex = re.compile('Australia[\r\n]')
  new_zealand_regex = re.compile('New Zealand[\r\n]')
  thailand_regex = re.compile('Thailand[\r\n]')
  china_regex = re.compile('China[\r\n]')
  chinese_taipei_regex = re.compile('Chinese Taipei[\r\n]')
  venezuela_regex = re.compile('Venezuela[\r\n]')
  south_korea_regex = re.compile('South Korea[\r\n]')
  northern_ireland_regex = re.compile('Northern Ireland[\r\n]')
  ireland_regex = re.compile('Ireland[\r\n]')
  japan_regex = re.compile('Japan[\r\n]')
  south_africa_regex = re.compile('South Africa[\r\n]')
  india_regex = re.compile('India[\r\n]')
  sweden_regex = re.compile('Sweden[\r\n]')
  norway_regex = re.compile('Norway[\r\n]')
  denmark_regex = re.compile('Denmark[\r\n]')
  canada_regex = re.compile('Canada[\r\n]')
  colombia_regex = re.compile('Colombia[\r\n]')
  mexico_regex = re.compile('Mexico[\r\n]')
  slovakia_regex = re.compile('Slovakia[\r\n]')
  scotland_regex = re.compile('Scotland[\r\n]')
  austria_regex = re.compile('Austria[\r\n]')
  italy_regex = re.compile('Italy[\r\n]')
  chile_regex = re.compile('Chile[\r\n]')
  puerto_rico_regex = re.compile('Puerto Rico[\r\n]')
  argentina_regex = re.compile('Argentina[\r\n]')
  germany_regex = re.compile('Germany[\r\n]')
  france_regex = re.compile('France[\r\n]')
  belgium_regex = re.compile('Belgium[\r\n]')
  
  temp_line = usa_regex.sub('',text)
  temp_line = spain_regex.sub('',temp_line)
  temp_line = england_regex.sub('',temp_line)
  temp_line = australia_regex.sub('',temp_line)
  temp_line = new_zealand_regex.sub('',temp_line)
  temp_line = thailand_regex.sub('',temp_line)
  temp_line = china_regex.sub('',temp_line)
  temp_line = venezuela_regex.sub('',temp_line)
  temp_line = south_korea_regex.sub('',temp_line)
  temp_line = northern_ireland_regex.sub('',temp_line)
  temp_line = ireland_regex.sub('',temp_line)
  temp_line = japan_regex.sub('',temp_line)
  temp_line = south_africa_regex.sub('',temp_line)
  temp_line = india_regex.sub('',temp_line)
  temp_line = sweden_regex.sub('',temp_line)
  temp_line = norway_regex.sub('',temp_line)
  temp_line = denmark_regex.sub('',temp_line)
  temp_line = canada_regex.sub('',temp_line)
  temp_line = colombia_regex.sub('',temp_line)
  temp_line = mexico_regex.sub('',temp_line)
  temp_line = scotland_regex.sub('',temp_line)
  temp_line = slovakia_regex.sub('',temp_line)
  temp_line = austria_regex.sub('',temp_line)
  temp_line = italy_regex.sub('',temp_line)
  temp_line = chile_regex.sub('',temp_line)
  temp_line = argentina_regex.sub('',temp_line)
  temp_line = puerto_rico_regex.sub('',temp_line)
  temp_line = chinese_taipei_regex.sub('',temp_line)
  temp_line = germany_regex.sub('',temp_line)
  temp_line = france_regex.sub('',temp_line)
  temp_line = belgium_regex.sub('',temp_line)

  temp_line = remove_accents(temp_line)

  return str(temp_line)
  
  
filename = input('Enter file to fix: ')

input_file = open (filename, 'r');

lines = input_file.readlines();

line_to_keep = []

for line in lines:
  temp_line = remove_countries(line)
  temp_line = remove_amateur(temp_line)
  temp_line = remove_end_of_name_carriage_return(temp_line)
  temp_line = remove_ties_carriage_return(temp_line)
  temp_line = remove_dash_carriage_return(temp_line)
  #temp_line = remove_position(temp_line)
  
  line_to_keep.append(temp_line)
  
#Somehow have to combine name with rest of score/money info line which is on next line
#name should be equal to what we get after call to remove_end_of_name_carriage_return
for line_temp in line_to_keep:
  print('line temp: ' + line_temp)
  
#####-Starting copy of new_fix_file.py stuff-#####
money_regex = re.compile(r'\$[0-9,]+')
cut_regex = re.compile('CUT')
withdrew_regex = re.compile('WD')
player_regex = re.compile(r'[A-Z][a-zA-Z\-.]* [a-zA-Z][a-zA-Z\-\']*( [A-Z][a-zA-Z-]*)*')

new_line_to_keep = []

for new_line in line_to_keep:
  if len(new_line) > 3:
    new_line_to_keep.append(new_line)
    
final_line_to_keep = []

money_value = '$0'
money_found = False

# Note that going into this loop, names are on their own line, followed by the
# rest of the scoring/earning information on the next line.
# The name is saved off and used when the earnings are found on the next line.
# Then the name and earnings is put on one line and saved into the
# 'final_line_to_keep' array

for final_line in new_line_to_keep:
   print('final line ' + final_line)
   if len(final_line) > 3:
         
     final_line_copy = final_line
     print('final line copy ' + final_line_copy)
     money = money_regex.search(final_line_copy)
     cut = cut_regex.search(final_line_copy)
     withdrew = withdrew_regex.search(final_line_copy)
     if money:
        print('money found')
        money_found = True
        money_value = money.group()
        #Remove commas from money
        money_without_commas  = remove_commas(money_value)
        print('setting money_value to ' + money_value)
        #final_line = player_to_print + ', ' + money_value + '\n'
        final_line = player_to_print + ', ' + money_without_commas + '\n'
        final_line_to_keep.append(final_line)
     elif cut:
        final_line = player_to_print + ', $0\n'
        final_line_to_keep.append(final_line)
     elif withdrew:
        final_line = player_to_print + ', $0\n'
        final_line_to_keep.append(final_line)
        
     player = player_regex.search(final_line)
     if player:
        player_to_print = player.group()
        print('player found: ' + player_to_print)           


new_filename = 'espn_' + filename;

output_file = open(new_filename, 'w')

output_file.writelines(final_line_to_keep)

input_file.close()
output_file.close()
  