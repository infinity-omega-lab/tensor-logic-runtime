# Persona Layer Spec — Public Edition (TL Runtime v0.7)
## Minimal Style & Routing Layer for TL Runtime

### 0. Overview
Persona Layer provides:
- Stylistic modulation
- Tone control
- Intent-to-style routing

It performs no reasoning, prediction, learning, memory retention, or optimization.

### 1. Scope
Covers:
- Style & tone
- Lightweight formatting
- Static descriptor-based routing

Does NOT include:
- Cognition, memory, prediction
- User modeling
- Safety policy logic

### 2. Persona Descriptor (Public Minimal Model)
```
PersonaDescriptor {
  slot_id: string,
  style_preset: string,
  tone_level: "neutral" | "warm" | "formal" | "technical",
  formality: "low" | "medium" | "high",
  override_rules?: {
      allow_user_priority?: boolean,
      enforce_minimal_output?: boolean
  },
  intents: string[]
}
```

### 3. JSON Schema (Public Edition)
```
{
  "type": "object",
  "properties": {
    "slot_id": { "type": "string" },
    "style_preset": { "type": "string" },
    "tone_level": {
      "type": "string",
      "enum": ["neutral", "warm", "formal", "technical"]
    },
    "formality": {
      "type": "string",
      "enum": ["low", "medium", "high"]
    },
    "override_rules": {
      "type": "object",
      "properties": {
        "allow_user_priority": { "type": "boolean" },
        "enforce_minimal_output": { "type": "boolean" }
      }
    },
    "intents": {
      "type": "array",
      "items": { "type": "string" }
    }
  },
  "required": ["slot_id", "style_preset", "tone_level", "formality", "intents"]
}
```

### 4. Persona Slot Behavior
Allowed:
- Tone modulation
- Formality adjustment
- Soft vocabulary shifts

Not Allowed:
- Semantic reinterpretation
- Intent inference
- Reasoning or learning

### 5. Override Rules (Public Edition)
```
OverrideRules {
  allow_user_priority: boolean,
  enforce_minimal_output: boolean
}
```

### 6. Intent–Slot Mapping
```
resolve_slot(intent_label: string) → slot_id
```

### 7. Minimal Persona API
```
PersonaAPI {
    load_descriptor(descriptor: PersonaDescriptor): SlotInfo
    apply_style(slot: SlotInfo, text: string, options?: ContextOptions): string
    resolve_slot(intent_label: string): SlotInfo
}
```

### 8. Safety Principles
Persona Layer is:
- Predictable
- Stateless
- Non-agentic
- Style-only

### 9. License Position
Safe for public + commercial use under TLCL OSS group.

# END OF PUBLIC SPEC
