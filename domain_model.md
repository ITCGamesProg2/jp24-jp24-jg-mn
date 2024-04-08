![Monika_src_cards](https://github.com/ITCGamesProg2/jp24-jp24-jg-mn/assets/115571613/949d3863-b766-4f1e-bbb1-83021bc9f38a)
![Katrina_src_cards](https://github.com/ITCGamesProg2/jp24-jp24-jg-mn/assets/115571613/7d17f44d-0d62-4625-8d4f-a3afc56acc5b)


classDiagram
    class Player {
        - positionX: int
        - positionY: int
        - score: int
        - lives: int
        + moveLeft()
        + moveRight()
        + moveUp()
        + moveDown()
        + shootProjectile()
        + collectItem()
    }

    class GameWorld {
        - boundaries: Rectangle
        - enemies: list<Enemy>
        - items: list<Item>
        + spawnEnemy()
        + spawnItem()
        + handleCollision()
    }

    class Enemy {
        - positionX: int
        - positionY: int
        + moveTowardsPlayer()
        + collideWithPlayer()
    }

    class Projectile {
        - positionX: int
        - positionY: int
        + move()
        + detectCollision()
    }

    class Item {
        - positionX: int
        - positionY: int
        + providePoints()
    }

    Player -- GameWorld : interacts with
    Player -- Enemy : collaborates with
    Player -- Item : collaborates with
    GameWorld -- Enemy : manages
    GameWorld -- Item : manages
    Enemy -- GameWorld : updates position
    Projectile -- Enemy : inflicts damage
    Projectile -- Player : fired by
    Item -- GameWorld : manages position
![Domain_Model](https://github.com/ITCGamesProg2/jp24-jp24-jg-mn/assets/115571613/cba39bb6-2897-4947-baa6-b38f4c1ca6df)


    
