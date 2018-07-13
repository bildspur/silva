package ch.bildspur.silva.configuration

import ch.bildspur.silva.Sketch
import ch.bildspur.silva.model.AppConfig
import ch.bildspur.silva.model.easing.EasingVector
import com.github.salomonbrys.kotson.fromJson
import com.github.salomonbrys.kotson.get
import com.google.gson.*
import processing.core.PVector
import java.lang.reflect.Type
import java.nio.file.Files
import java.nio.file.Path
import java.nio.file.Paths


/**
 * Created by cansik on 11.07.17.
 */
class ConfigurationController {
    companion object {
        @JvmStatic
        val CONFIGURATION_FILE = "${Sketch.URI_NAME}.json"

        @JvmStatic
        val CONFIGURATION_DIR: Path = Paths.get("config")

        @JvmStatic
        val CONFIGURATION_PATH: Path = Paths.get(CONFIGURATION_DIR.toString(), CONFIGURATION_FILE)
    }

    val gson: Gson = GsonBuilder()
            .setPrettyPrinting()
            .excludeFieldsWithoutExposeAnnotation()
            .registerTypeAdapter(PVector::class.java, PVectorSerializer())
            .registerTypeAdapter(PVector::class.java, PVectorDeserializer())
            .registerTypeAdapterFactory(PostProcessingEnabler())
            .create()

    fun loadAppConfig(): AppConfig {
        if (!Files.exists(CONFIGURATION_DIR)) {
            Files.createDirectories(CONFIGURATION_DIR)
            saveAppConfig(AppConfig())
        }

        return loadData(CONFIGURATION_PATH)
    }

    fun saveAppConfig(config: AppConfig) {
        saveData(CONFIGURATION_PATH, config)
    }

    inline fun <reified T : Any> loadData(configFile: Path): T {
        val content = String(Files.readAllBytes(configFile))
        return gson.fromJson(content)
    }

    inline fun <reified T : Any> saveData(configFile: Path, config: T) {
        val content = gson.toJson(config)
        Files.write(configFile, content.toByteArray())
    }

    private inner class PVectorDeserializer : JsonDeserializer<PVector> {
        override fun deserialize(json: JsonElement, typeOfT: Type, context: JsonDeserializationContext): PVector {
            val x = json["x"].asFloat
            val y = json["y"].asFloat
            val z = json["z"].asFloat
            return PVector(x, y, z)
        }
    }

    private inner class PVectorSerializer : JsonSerializer<PVector> {
        override fun serialize(src: PVector, typeOfSrc: Type, context: JsonSerializationContext): JsonElement {
            val obj = JsonObject()
            obj.addProperty("x", src.x)
            obj.addProperty("y", src.y)
            obj.addProperty("z", src.z)
            return obj
        }
    }
}