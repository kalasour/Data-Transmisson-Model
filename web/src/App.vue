<template>
  <v-app>
    <v-toolbar app>
      <v-toolbar-title class="headline text-uppercase">
        <span>Vuetify</span>
        <span class="font-weight-light">MATERIAL DESIGN</span>
      </v-toolbar-title>
      <v-spacer></v-spacer>
      <v-btn flat href="https://github.com/vuetifyjs/vuetify/releases/latest" target="_blank">
        <span class="mr-2">Latest Release</span>
      </v-btn>
    </v-toolbar>

    <v-content>
      <!-- <HelloWorld/> -->
      <template>
        <v-list>
          <v-list-tile v-for="(item,index) in chat" :key="index">
            <v-list-tile-content>
              <v-list-tile-title v-text="item"></v-list-tile-title>
            </v-list-tile-content>
          </v-list-tile>
        </v-list>
        <v-form v-model="valid" v-on:submit.prevent="send">
          <v-container>
            <v-layout>
              <v-flex xs12 md12>
                <v-text-field
                  :disabled="!canSend"
                  v-model="message"
                  :label="canSend?'Aa':'sending...'"
                  required
                ></v-text-field>
              </v-flex>
            </v-layout>
          </v-container>
        </v-form>
      </template>
    </v-content>
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
      if (JSON.parse(data.data).D != null&&JSON.parse(data.data).D != '\n') this.chat.push(JSON.parse(data.data).D)
    };
  },
  data() {
    return {
      chat: [],
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
