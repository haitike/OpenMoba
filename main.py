#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Modules
import random, os, pygame
from pygame.locals import *

# Constants
SCREEN_WIDTH  = 800
SCREEN_HEIGHT = 600
DATA = "data"

# Class
class Champion(pygame.sprite.Sprite):

    def __init__(self):
        pygame.sprite.Sprite.__init__(self)
        self.image, self.rect = load_image("champion.png", True)
        self.rect.center = (SCREEN_WIDTH/2,SCREEN_HEIGHT)
        self.x_velocity = 0
        self.y_velocity = 0

    def update(self):
        self.rect.move_ip((self.x_velocity, self.y_velocity))

        # Limits
        if self.rect.left < 0:
            self.rect.left = 0
        elif self.rect.right > SCREEN_WIDTH:
            self.rect.right = SCREEN_WIDTH
        if self.rect.top <= 0:
            self.rect.top = 0
        elif self.rect.bottom >= SCREEN_HEIGHT:
            self.rect.bottom = SCREEN_HEIGHT
            
 
class Minion( pygame.sprite.Sprite ):

    def __init__(self, startx):
        pygame.sprite.Sprite.__init__(self)
        self.image, self.rect = load_image("champion.png", True)
        self.rect.centerx = startx
        self.rect.centery = -50
        self.x_velocity = random.randint(-3+puntos/250, 3+puntos/250)
        self.y_velocity = random.randint(-3+puntos/250, 3+puntos/250)
        
    def update( self):
        self.rect.move_ip((self.x_velocity, self.y_velocity))

        # Movements
        if self.rect.left < 0 or self.rect.right > SCREEN_WIDTH:
            self.x_velocity = -(self.x_velocity)
        if self.rect.top < -80 or self.rect.bottom > SCREEN_HEIGHT/2:
            self.y_velocity = -(self.y_velocity)

        #Random Attacks
        if puntos < 600:  
                fire  = random.randint(1, 120 - (puntos/10))
        else : 
            fire = random.randint(1, 20)
        if fire == 1:
            minionAttackSprites.add(minionAttack(self.rect.midbottom))
            minionShotFX.play()

class ChampionAttack(pygame.sprite.Sprite):
    
    def __init__(self, startx, starty):
        pygame.sprite.Sprite.__init__(self)
        self.image, self.rect = load_image("laser.bmp", True)
        self.rect.centerx = startx
        self.rect.centery = starty

    def update( self ):
        
        if self.rect.bottom <= -80:
            self.kill() 
        else:
            self.rect.move_ip((0,-6))
            
class MinionAttack(pygame.sprite.Sprite):
    
    def __init__(self, startpos):
        pygame.sprite.Sprite.__init__(self)
        self.image, self.rect = load_image("laser.bmp", True)
        self.rect.midtop = startpos
        
    def update( self):
         
        if self.rect.bottom >= SCREEN_HEIGHT:
            self.kill()
        else:
            if puntos > 200:
                self.rect.move_ip(random.randint(-(puntos-200)/30 ,(puntos-200)/30),4+(puntos/100)) #Si no, seguimos subiendo
            else:
                self.rect.move_ip(0,4+(puntos/100))

def load_image(name, colorkey = False):    
    fullname = os.path.join(DATA, name)
    try: image = pygame.image.load(fullname)
    except pygame.error, message:
        print 'The image could not be loaded: ', fullname
        raise SystemExit, message  
    image = image.convert()
    if(colorkey): 
        colorkey = image.get_at((0,0))
        image.set_colorkey(colorkey, RLEACCEL)
    return image, image.get_rect()

def load_SoundFile(name):

    class NoneSound:
        def play(self): pass
    if not pygame.mixer or not pygame.mixer.get_init():
        return NoneSound()
    fullname = os.path.join(DATA, name)
    try:
        sound = pygame.mixer.Sound(fullname)
    except pygame.error, message:
        print "The sound wasn't unable to load:", fullname
        raise SystemExit, message
    return sound
 
def main():
    global puntos
    temp = "0,0"
    puntos = 0
    running = True
    live = 0 
    attack_speed = 1.0
    attack_misiles = 2
    global retardo
    retardo = 150 
    global SCREEN_WIDTH 
    global SCREEN_HEIGHT
    
    #Starting Things
    random.seed()
    pygame.init()
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT), HWSURFACE|DOUBLEBUF)
    pygame.display.set_caption( "OpenMoba" )
    background_image, background_rect = load_image("background.bmp")
    screen.blit(background_image, (0,0))
    
    # Loading sounds
    explodeFX = load_SoundFile( "explode1.wav" )
    minionShotFX = load_SoundFile( "empire_laser.wav" )
    championFX = load_SoundFile( "rebel_laser.wav" )

    # Starting Sprites
    championSprite = pygame.sprite.RenderClear()
    champion = Champion()
    championSprite.add(champion)
    championAttackSprites = pygame.sprite.RenderClear()
    minionSprites = pygame.sprite.RenderClear()
    global minionAttackSprites
    minionAttackSprites = pygame.sprite.RenderClear()

    #Control Stuff
    clock = pygame.time.Clock()
    while running is True:
        clock.tick(75) # 75 frames per second
        
        # Events
        for event in pygame.event.get():
            if event.type == QUIT:
                running = False # Game End
            elif event.type == MOUSEBUTTONDOWN:
                if event.button == 3:
                    temp = str(event.pos)
                    ataque_base(attack_misiles)
            elif event.type == KEYDOWN:
                if event.key == K_ESCAPE:
                    running = False # Se acaba el juego
                elif event.key == K_LEFT:
                    champion.x_velocity = -4
                elif event.key == K_RIGHT:
                    champion.x_velocity = 4
                elif event.key == K_UP:
                    champion.y_velocity = -4
                elif event.key == K_DOWN:
                    champion.y_velocity = 4
                elif event.key == K_SPACE:
                    ataque_base(attack_misiles)
            elif event.type == KEYUP:
                if event.key == K_LEFT:
                    champion.x_velocity = 0
                elif event.key == K_RIGHT:
                    champion.x_velocity = 0
                elif event.key == K_UP:
                    champion.y_velocity = 0
                elif event.key == K_DOWN:
                    champion.y_velocity = 0

        #ataque base
        if retardo < 150.0+(attack_speed-1.1)*100  :
            retardo += attack_speed
        else:
            retardo = 150.0+(attack_speed-1.1)*100      
        def ataque_base(attack_misiles):
            global retardo
            if retardo >= 50.0:
                for i in range(attack_misiles):
                    if attack_misiles >= 2:
                        championAttackSprites.add(ChampionAttack(champion.rect.centerx -attack_misiles*6 + 15*i, champion.rect.centery -30))
                    else:
                        championAttackSprites.add(ChampionAttack(champion.rect.centerx, champion.rect.centery -30))
                championFX.play()
                retardo -= 50.0
                
        # Updating Sprites
        championSprite.update()
        championAttackSprites.update()
        minionSprites.update()
        minionAttackSprites.update()

        # Collisions
        for hit in pygame.sprite.groupcollide( minionSprites, championAttackSprites, 1, 1):
            explode1FX.play()
            puntos = puntos + 1
            if semen < max_semen:
                if semen > max_semen - 1 : semen = max_semen -1
                semen = semen + 1
        for hit in pygame.sprite.groupcollide( championSprite, minionAttackSprites, 1, 1):
            explode1FX.play()
            running = False # Se acaba el juego
        for hit in pygame.sprite.groupcollide( championSprite, minionSprites, 1, 1):
            explode1FX.play()
            running = False # Se acaba el juego
        for hit in pygame.sprite.groupcollide( championAttackSprites, minionAttackSprites, 1, 1):
            if semen < max_semen:
                semen = semen + 0.2
                
        # Cleaning
        minionAttackSprites.clear( screen, background_image )
        minionSprites.clear( screen, background_image )
        championAttackSprites.clear( screen, background_image)
        championSprite.clear( screen, background_image )        

        # Text Print
        fonte = pygame.font.Font(None, 55)
        text = fonte.render(temp + "  " + str(puntos), 1,(255,255,255,0))
        text2 = fonte.render(str("A"), 1,(255,255,255,0))
        text3 = fonte.render(str("¡A!"), 1,(255,255,255,0))
        screen.blit(background_image, (0,0))
        screen.blit(text, (560,20))
        
        # Draw
        minionAttackSprites.draw( screen )
        championAttackSprites.draw( screen )
        minionSprites.draw( screen )
        championSprite.draw( screen )

        pygame.display.flip()
        #raise SystemExit

    return 0
    
if __name__ == '__main__': 
    main()
