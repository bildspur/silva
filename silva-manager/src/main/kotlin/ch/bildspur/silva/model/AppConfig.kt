package ch.bildspur.silva.model

import com.google.gson.annotations.Expose

class AppConfig {
    @Expose val defaultLeafCount = 26

    @Expose val leafs : MutableList<Leaf> = mutableListOf()
}