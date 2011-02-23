#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Modules
import random, os, pygame
import language # Internalization File (language.py)
from pygame.locals import *

# Constants
SCREEN_WIDTH  = 800
SCREEN_HEIGHT = 600
DATA = "data"

# Classes
class Champion(pygame.sprite.Sprite):

    def __init__(self):
        pygame.sprite.Sprite.__init__(self)
        self.image, self.rect = load_image("champion.png", True)
        self.rect.center = (SCREEN_WIDTH/2,SCREEN_HEIGHT)
        self.cursor = self.rect.center
        self.x_velocity = 0
        self.y_velocity = 0

    def update(self):        
        # Movement Command Directions (Right Click with mouse)
        # self.cursor[0] = position x on click 
        # self.cursor[1] = position y on click
        if self.rect.centerx > self.cursor[0]: self.x_velocity = -1
        elif self.rect.centerx < self.cursor[0]: self.x_velocity = 1
        else: self.x_velocity = 0
    
        if self.rect.centery > self.cursor[1]: self.y_velocity = -1
        elif self.rect.centery < self.cursor[1]: self.y_velocity = 1
        else: self.y_velocity = 0    
        
        # Movement
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

    def attack(self, attacks, sprites):
        for i in range(attacks):
            if attacks >= 2: # If more than 1 proyectiles per attack
                sprites.add(ChampionAttack(self.rect.centerx -attacks*6 + 15*i, self.rect.centery -30))
            else:
                sprites.add(ChampionAttack(self.rect.centerx, self.rect.centery -30))
        
    def getCursor(self,mouse):
        self.cursor = mouse    

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
            

class Minion( Champion ): # TODO
    pass

class MinionAttack( ChampionAttack ): # TODO
    pass

def load_image(name, colorkey = False):    
    fullname = os.path.join(DATA, name)
    try: image = pygame.image.load(fullname)
    except pygame.error, message:
        print _('The image could not be loaded: '), fullname
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
        print _("The sound wasn't unable to load:"), fullname
        raise SystemExit, message
    return sound
 
def main():
    running = True # If False the game ends.
    temp = "0,0" # Borrar
    puntos = 0
    misile_number = 2
    
    #Starting Things
    random.seed()
    pygame.init()
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT), HWSURFACE|DOUBLEBUF)
    pygame.display.set_caption( "OpenMoba" )
    background_image, background_rect = load_image("background.png")
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
    minionAttackSprites = pygame.sprite.RenderClear()

    #Control Stuff
    clock = pygame.time.Clock()
    while running is True:
        clock.tick(75) # 75 frames per second
        
        # Events
        for event in pygame.event.get():
            if event.type == QUIT:
                running = False
            elif event.type == MOUSEBUTTONDOWN:
                if event.button == 3:
                    temp = str(event.pos)
                    champion.getCursor(event.pos)
            elif event.type == KEYDOWN:
                if event.key == K_ESCAPE:
                    running = False
                elif event.key == K_SPACE:
                    champion.attack(misile_number,championAttackSprites)
                    championFX.play()
                          
        # Updating Sprites
        championSprite.update()
        championAttackSprites.update()
        minionSprites.update()
        minionAttackSprites.update()

        # Collisions
        for hit in pygame.sprite.groupcollide( minionSprites, championAttackSprites, 1, 1):
            explodeFX.play()
            puntos = puntos + 1
        for hit in pygame.sprite.groupcollide( championSprite, minionAttackSprites, 1, 1):
            explodeFX.play()
            running = False
        for hit in pygame.sprite.groupcollide( championSprite, minionSprites, 1, 1):
            explodeFX.play()
            running = False
        for hit in pygame.sprite.groupcollide( championAttackSprites, minionAttackSprites, 1, 1):
            pass
                
        # Cleaning
        minionAttackSprites.clear( screen, background_image )
        minionSprites.clear( screen, background_image )
        championAttackSprites.clear( screen, background_image)
        championSprite.clear( screen, background_image )        

        # Text Print
        font = pygame.font.Font(None, 55)
        text = font.render(_("Mouse:") + temp + _(" | Kills: ") + str(puntos), 1,(255,255,255,0))
        screen.blit(background_image, (0,0))
        screen.blit(text, (200,10))
        
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
