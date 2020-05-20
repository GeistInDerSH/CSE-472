#!/bin/python3
"""
	This file is used to collect the data that will later be graphed
"""
import tweepy
import csv
import json
import time

# All 118 followers of @Pamplemouss_
X_followers = [
'@damln',
'@GH0S1',
'@TeknO_01010',
'@DevDog74923971',
'@AMathTuring',
'@sewell_jason',
'@david_scrobonia',
'@_amanvir',
'@TrabelsiAmani2',
'@_Grominet',
'@claucece',
'@coni2k',
'@NatWuestenfuchs',
'@AnnaBurkhart',
'@natalieesk',
'@learner213',
'@jasminehenry10',
'@johto1989',
'@_ifthenelse_',
'@EasyCrypt_co',
'@OuiSouss',
'@tkeetch',
'@ThylaVdMerwe',
'@xopek59',
'@GM_K4J4N',
'@_guttula',
'@psiinon',
'@chauhan__harry',
'@YassineAlouini',
'@define__tosh__',
'@HowieMeg',
'@yayamamass',
'@n0vemberHalf9',
'@RailsBridgeWgtn',
'@bassilissa',
'@ntoreky',
'@AudreyFaugere',
'@doruksepit1',
'@vincenthetru',
'@bonj_alexandre',
'@anthony_don',
'@DjangoGirlsBdx',
'@ChrisHeral',
'@thexfifix',
'@pocauzorus',
'@DocFusion',
'@CeratoRomain',
'@DubiousOtter',
'@MaTanZa2OO3',
'@libNex',
'@ltsbigj',
'@LMH_nouveau',
'@cuberri',
'@VinLew',
'@NicoLetoublon',
'@CodePourFrance',
'@sylvain_lefran',
'@636172746d',
'@akampjes',
'@safiler',
'@charlieed49',
'@NZ_IT_Agent',
'@axoc',
'@guillaume20100',
'@Pam_HML',
'@ArnoAllar',
'@habsinn',
'@mikael_letang',
'@strycore',
'@MetildeMz',
'@BLASTKORE',
'@nostradamnit',
'@cedricnehemie',
'@bastien_gallay',
'@pommeDouze',
'@edouard_lopez',
'@PoubellesMaps',
'@shoxxdj',
'@reverseth',
'@elogeay',
'@TristanDanzi',
'@benjamet',
'@SoftwareAngels',
'@totolarr',
'@XavierReculin',
'@keronos',
'@datalocale',
'@YannSrt',
'@Ulrich_Cadart',
'@JuliaSanchez92',
'@Rainarkan',
'@acide_ici',
'@AnyssiaB',
'@tonio3313',
'@HeleneChance',
'@_shadow_it',
'@natiatia',
'@obusco',
'@ScouserandBx',
'@jbduzan',
'@ptiben_yolt',
'@NicolasJouffrau',
'@Cook_King_News',
'@CoLoqueTV',
'@remiolivier',
'@MartiniJus',
'@Jahlucine',
'@Dragibus_Soft',
'@Tronix117',
'@_leveque',
'@jmarrot33',
'@_alram',
'@nyx__o',
'@dqms_output',
'@sebvita',
'@JaiPasInternet',
'@megmouth',
'@MoOnLiGht_WW']

# Create a list with the same number of locations
# as there are people in the X_followers list
lst = [None] * len(X_followers)

# Set the authorization credentials
consumer_key = ''
consumer_secret = ''
access_key = ''
access_secret = ''

# Make an authorization request to twitter
auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_key,access_secret)
api = tweepy.API(auth)

# Determine what position inside of lst the followers will be
# inserted into
insert_loc=0
for i in X_followers:
    print(str(i))
    users = tweepy.Cursor(api.followers, screen_name=str(i)).items()

    # Set the follower count to be zero
    count = 0

    # For the first 100 Followers of the person
    while count < 100:
    	# Try and get the next follower in the list
        try:
            user = next(users)
            count+=1

	# If there have been to many requests in the 15 minute
	# block, sleep for 15 minutes
        except tweepy.TweepError:
            time.sleep(60*15)
            break

	# If there are no more followers, increment where we are
	# inserting the followers and break out of this loop
        except StopIteration:
            insert_loc+=1
            break

	# Print the twitter followers to the screen
        print( "\t@" + user.screen_name)

	# Add the follower to the list of followers
        lst.insert(insert_loc, "@" + user.screen_name)

    # Print out how many followers the user has ( or the number of followers
    # that were parsed)
    print("%s has %d followers\n\n" % (str(i), count))
