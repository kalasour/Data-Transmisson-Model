<template>
  <v-app style="background: #3A1C71;background: linear-gradient(to right, #FFAF7B, #D76D77, #3A1C71);" >
    <v-toolbar color="#FFCCBC" app >
      <v-toolbar-title style="font-family: Comic Sans MS, serif; font-size:20pt">
        LIGHT CHAT
      </v-toolbar-title>
      <v-spacer></v-spacer>
      <v-btn flat href="https://github.com/vuetifyjs/vuetify/releases/latest" target="_blank">
        <span class="mr-2"></span>
      </v-btn>
    </v-toolbar>
   
   <!-- content -->
    <v-content grid-list-md> 
      <!-- <HelloWorld/> -->
      
       <v-layout row >
      
        
        <v-flex xs6>
        <v-card style="  width: 550px;
                         padding: 50px;
                         margin: auto;
                         margin-top:120px;
                         border-radius: 5px;">
                   
        <v-form v-model="valid" v-on:submit.prevent="send">
          <v-container class="back">
            <v-layout>
              <v-flex xs12 md12>
                <v-text-field
                  :counter="30"
                  :disabled="!canSend"
                  v-model="message"
                  :label="canSend?'text me!!':'sending...'"
                  required
                ></v-text-field>
              </v-flex>
            </v-layout>
          </v-container>
        </v-form>
      </v-card>
        </v-flex>

        <v-flex xs6>
          
        <v-card style="  background:#FFCCBC;
                         width: 550px;
                         margin: auto;
                         margin-top:120px;
                         border-radius: 5px;">
        <v-list>
          <v-list-tile v-for="(item,index) in chat" :key="index">
            <v-list-tile-content>
              <v-list-tile-title v-text="item"></v-list-tile-title>
            </v-list-tile-content>
          </v-list-tile>
        </v-list>
        </v-card>
      </v-flex>

      </v-layout>
     
    </v-content>
   
    
    <!-- footer -->
   
  <v-footer class="pa-3" style="background-color:#9E9E9E;">
    <v-spacer></v-spacer>
    <div>GROUP 1.2 DATA TRANSMISSION MODEL</div>
  </v-footer>

  </v-app>
</template>


<script>
// import HelloWorld from "./components/HelloWorld";
var ws = new WebSocket("ws://localhost:8888/");
var rev = new WebSocket("ws://localhost:8989/ws");
console.log("connecting to Sender server...");

export default {
  name: "App",
  components: {},
  created() {
    ws.onopen = () => {
      console.log("connected to Sender server!");
    };

    ws.onmessage = (data, flags) => {
      if (data.data == "Input:\n") {
        this.canSend = true;
      }
    };

    rev.onopen = () => {
      console.log("connected to Reciever server!");
    };

    rev.onmessage = (data, flags) => {
      // console.log(data.data)
      if (JSON.parse(data.data).D != null && JSON.parse(data.data).D != "\n")
        this.chat.push(JSON.parse(data.data).D);
    };
  },
  data() {
    return {
      chat: ["cfghcfh", "fhskkjllkjkljn","dfghjkl;"],
      canSend: true,
      valid: false,
      message: ""
    };
  },
  methods: {
    send() {
      this.canSend = false;
      ws.send(this.message);
      this.message = "";
    }
  }
};
</script>
