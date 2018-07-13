package ch.bildspur.silva.model

import com.google.gson.annotations.Expose

class AppConfig {
    @Expose val oscInPort = 9000

    @Expose val oscOutPort = 8000

    @Expose val defaultLeafCount = 26

    @Expose val leafs : MutableList<Leaf> = mutableListOf()
}